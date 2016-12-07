#pragma once

#include <Windows.h>
#include "Lights.h"
#include "Shader.h"
#include "Math/Vector.h"
#include "GeometryGenerator.h"
#include "_3DDevice.h"



template <typename T>
class Box
{

public:
	Box() : theta_(static_cast<T>(1.5 * PI)), phi_(static_cast<T>(0.4 * PI)),
		radius_(static_cast<T>(5.0f))
	{
		lastMousePos_.x = 0;
		lastMousePos_.y = 0;

		world_ = world_.Identity();

		
		
		// 平行光
		dirLight_.ambient_ = Vector4<T>(static_cast<T>(0.7f),
										static_cast<T>(0.7f),
										static_cast<T>(0.7f),
										static_cast<T>(1.0f));
		
		dirLight_.diffuse_ = Vector4<T>(static_cast<T>(0.5f),
										static_cast<T>(0.5f),
										static_cast<T>(0.5f),
										static_cast<T>(1.0f));
		
		dirLight_.specular_ = Vector4<T>(static_cast<T>(0.5f),
										static_cast<T>(0.5f),
										static_cast<T>(0.5f)); 
		
		
		dirLight_.direction_ = Vector4<T>(static_cast<T>(0.57735f),
										static_cast<T>(0.57735f),
										static_cast<T>(0.57735f));
									
		
		
		// 材质
		material_.ambient_ = Vector4<T>(static_cast<T>(0.7f),
										static_cast<T>(0.85f),
										static_cast<T>(0.7f),
										static_cast<T>(1.0f));

		
		material_.diffuse_ = Vector4<T>(static_cast<T>(0.7f),
										static_cast<T>(0.85f),
										static_cast<T>(0.7f),
										static_cast<T>(1.0f));

		material_.specular_ = Vector4<T>(static_cast<T>(0.8f),
										static_cast<T>(0.85f),
										static_cast<T>(0.8f),
										static_cast<T>(16.0f));
	
	}


	
	~Box()
	{
		Clear();
	}

public:
	bool Init(HINSTANCE hInstance, HWND hWnd)
	{
		
		hWnd_ = hWnd;
		hInstance_ = hInstance;
		RECT rc;
		GetClientRect(hWnd_, &rc);
		width_ = rc.right - rc.left;
		height_ = rc.bottom - rc.top;

		pBaseDevice_ = new Base_3DDevice <T>(width_, height_);
		pDevice_ = new _3DDevice <T>();
		pDevice_->Init(pBaseDevice_);
		pShader_ = new Shader<T>;



		// 创建顶点缓存
		GeometryGenerator<T>::GetInstance()->CreateBox(static_cast<T>(2.0f),
														static_cast<T>(2.0f),
														static_cast<T>(2.0f),
														box_);

		vertices_.resize(box_.vertices_.size());
		for (size_t i = 0; i < box_.vertices_.size(); ++i) {
			vertices_[i].pos_ = box_.vertices_[i].pos_;
			vertices_[i].tex_ = box_.vertices_[i].tex_;
			vertices_[i].normal_ = box_.vertices_[i].normal_;
			vertices_[i].color_ = box_.vertices_[i].color_;
		}

		pDevice_->SetVertexBuffer(vertices_);

		// 创建索引缓存
		indices_.resize(box_.indices_.size());
		for (size_t i = 0; i < box_.indices_.size(); ++i) {
			indices_[i] = box_.indices_[i];
		}

		pDevice_->SetIndexBuffer(indices_);

		
		
		//设置着色器
		pDevice_->SetShader(pShader_);

		// 加载纹理
		T tip = static_cast<T>(0.0f);
		tex_ = Make_Tex_Rainbow(tip);

		// 设置着色器纹理
		// 由于纹理加载一次
		pShader_->SetTexture(tex_);
		


		// 设置着色器光源、材质
		pShader_->SetDirLight(dirLight_);
		pShader_->SetMaterial(material_);

		return true;
	}

	void Update(T dt)
	{
		
		T x = radius_ * sin(phi_) * cos(theta_);
		T y = radius_ * cos(phi_);
		T z = radius_ * sin(phi_) * sinf(theta_);

		Vector4 <T> pos(x, y, z, static_cast<T>(1.0f));
		Vector4 <T> target(static_cast<T>(0.0f), static_cast<T>(0.0f),
							static_cast<T>(0.0f), static_cast<T>(1.0f));
		Vector4 <T> up(static_cast<T>(0.0f), static_cast<T>(1.0f),
							static_cast<T>(0.0f), static_cast<T>(0.0f));

		Matrix <T> view, proj, world;
		view = view.LookAtLH(pos, target, up);
		proj = proj.PerspectiveFovLH(static_cast<T>(PI / 4.0),
									static_cast<T>(pBaseDevice_->GetClientWidth()) /
									static_cast<T>(pBaseDevice_->GetClientHeight()), 
									static_cast<T>(1.0f), static_cast<T>(100.f));

		world = world.Identity();
		worldViewProj_ = world * view * proj;
		world_ = world;

		// 计算逆矩阵的转置
		worldInvTranspose_ = world.Inverse().Transpose();

		// 设置相机位置 以便背面消隐
		pDevice_->SetCameraPos(pos);

		// 设置着色器中eyePos
		pShader_->SetEyePos(pos);
		
	}

	void Render()
	{
		// 设置后缓冲图片
		pBaseDevice_->ClearBuffer(Vector4 <T>(static_cast<T>(0.75f),
									static_cast<T>(0.75f),
									static_cast<T>(0.75f)));

		// 设置渲染状态
		pDevice_->SetRenderMode(_3D_FILL_MODE::_3D_FILL_SOLIDE);

		// 设置着色器变量
		pShader_->SetWorldViewProj(worldViewProj_);
		pShader_->SetWorld(world_);
		pShader_->SetWorldInvTranspose(worldInvTranspose_);

		pDevice_->DrawIndexed(indices_.size(), 0, 0);
		
	}

	void Clear()
	{
		if (pBaseDevice_) {
			delete pBaseDevice_;
		}

		if (pDevice_) {
			delete pDevice_;
		}

		if (pShader_) {
			delete pShader_;
		}
	}


	// 鼠标事件控制
	void OnMouseDown(WPARAM btnState, int x, int y)
	{
		lastMousePos_.x = x;
		lastMousePos_.y = y;
		SetCapture(hWnd_);
	}

	void OnMouseUp(WPARAM btnState, int x, int y)
	{
		ReleaseCapture();
	}

	void OnMouseMove(WPARAM btnState, int x, int y)
	{
		
		if ((btnState & MK_LBUTTON) != 0) {
			// 角度转弧度
			T dx = ConvertToRadians(static_cast<T>(0.25f) * static_cast<T>(x - lastMousePos_.x));
			T dy = ConvertToRadians(static_cast<T>(0.25f) * static_cast<T>(y - lastMousePos_.y));
		
			theta_ -= dx;
			phi_ += dy;

			if (phi_ >= static_cast<T>(PI - 0.0001)) {
				phi_ = static_cast<T>(0.001f);
			}
			else if (phi_ < static_cast<T>(0.0001f)) {
				phi_ = static_cast<T>(2.0 * PI - 0.001);
			}

			//phi_ = Clamp(phi_, static_cast<T>(0.1f), static_cast<T>(PI - 0.1));
		}
		else if ((btnState & MK_RBUTTON) != 0) {
			T dx = static_cast<T>(0.2f) * static_cast<T>(x - lastMousePos_.x);
			T dy = static_cast<T>(0.2f) * static_cast<T>(y - lastMousePos_.y);

			radius_ += dx - dy;

			radius_ = Clamp(radius_, static_cast<T>(4.7f), static_cast<T>(80.0f));

		}

		lastMousePos_.x = x;
		lastMousePos_.y = y;
		
	}

public:
	inline Base_3DDevice <T>*& GetDevice()
	{
		return pBaseDevice_;
	}

	

private:
	int								width_, height_;
	HINSTANCE						hInstance_;
	HWND							hWnd_;

	Base_3DDevice <T>				*pBaseDevice_;
	_3DDevice <T>					*pDevice_;
	Shader <T>						*pShader_;

	Matrix <T>						worldViewProj_;					// 世界视角投影矩阵
	Matrix <T>						world_;							// 世界变换矩阵
	Matrix <T>						worldInvTranspose_;				// 世界变换逆矩阵的转置 用于调整法线



	std::vector<VertexIn <T>>		vertices_;						//顶点缓冲
	std::vector<unsigned int>		indices_;						//索引缓冲

	_MeshData <T>	box_;

	Texture2D <T>					tex_;							//纹理

	Lights::Material <T>			material_;						//材质
	Lights::DirectionalLight <T>	dirLight_;						//平行光源

																	//控制摄像机位置角度等
	T								theta_;
	T								phi_;
	T								radius_;
	POINT							lastMousePos_;
};