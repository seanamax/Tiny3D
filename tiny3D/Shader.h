#pragma once

#include "Base_Shade.h"
#include "Math/Math.h"
#include "Vertex.h"
#include "Texture2D.h"

template <typename T>
class Shader : public ShaderBase <T>
{
public:
	Shader()
	{

	}

	virtual ~Shader()
	{

	}


public:
	void SetWorldViewProj(const Matrix <T>& worldViewProj)
	{
		worldViewProj_ = worldViewProj;
	}

	void SetTexture(const Texture2D <T>& tex)
	{
		tex_ = tex;
	}

	void SetWorld(const Matrix <T>& world)
	{
		world_ = world;
	}

	void SetWorldInvTranspose(const Matrix <T>& worldInvTrans)
	{
		worldInvTranspose_ = worldInvTrans;
	}

	void SetEyePos(const Vector4 <T> eyePos)
	{
		eyePos_ = eyePos;
	}

	void SetMaterial(const Lights::Material <T>& material)
	{
		material_ = material;
	}

	void SetDirLight(const Lights::DirectionalLight <T>& dirLight)
	{
		dirLight_ = dirLight;
	}


public:
	virtual VertexOut<T> VS(const VertexIn <T>& vin) 		// 顶点着色器
	{
		VertexOut <T> out;
		out.posH_ = Vec4MutiMat(vin.pos_, worldViewProj_);

		out.posTrans_ = Vec4MutiMat(vin.pos_, world_);
		out.normal_ = Vec4MutiMat(out.normal_, worldInvTranspose_);

		out.color_ = vin.color_;
		out.tex_ = vin.tex_;

		return out;
	}

	 virtual Vector4<T> PS(VertexOut <T>& pin)
	{

		pin.normal_ = pin.normal_.Normalize();

		Vector4 <T> texColor = tex_.Sample(pin.tex_);

		Vector4 <T> toEye = (eyePos_ - pin.posTrans_).Normalize();

		Vector4 <T> ambient(static_cast<T>(0.0f),
						    static_cast<T>(0.0f),
							static_cast<T>(0.0f),
							static_cast<T>(0.0f));

		Vector4 <T> diffuse(static_cast<T>(0.0f),
							static_cast<T>(0.0f),
							static_cast<T>(0.0f),
							static_cast<T>(0.0f));

		Vector4 <T> specular(static_cast<T>(0.0f),
							static_cast<T>(0.0f),
							static_cast<T>(0.0f),
							static_cast<T>(0.0f));

		Vector4 <T> A, D, S;

		Lights::ComputeDirectionalLight(material_, dirLight_, pin.normal_, toEye, A, D, S);

		ambient = ambient + A;
		diffuse = diffuse + D;
		specular = specular + S;

		Vector4 <T> litColor = texColor * (ambient + diffuse) + specular;

		litColor.w_ = material_.diffuse_.w_ * texColor.w_;

		return litColor;

	}


	private:
		Matrix <T>						worldViewProj_;			// 世界视角投影矩阵
		Texture2D <T>					tex_;					// 纹理
		Matrix <T>						world_;					// 世界矩阵
		Matrix <T>						worldInvTranspose_;		// 世界矩阵逆矩阵的转置，用于调整法线
		Lights::Material <T>			material_;				// 材质
		Lights::DirectionalLight <T>	dirLight_;				// 平行光
		Vector4 <T>						eyePos_;				// 观察点
};