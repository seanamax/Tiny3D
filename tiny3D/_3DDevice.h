#pragma once

#include "Base_3DDevice.h"
#include "Math/Math.h"
#include "Vertex.h"
#include "Texture2D.h"
#include "Base_Shade.h"

enum class _3D_FILL_MODE
{
	_3D_FILL_WIREFRAME,	// 线框模式
	_3D_FILL_SOLIDE		// 实体模式
};

template <typename T>
class _3DDevice
{
public:
	_3DDevice() : renderMode_(_3D_FILL_MODE::_3D_FILL_WIREFRAME),
				cameraPos_(Vector4 <T>(static_cast<T>(0.0f),
									   static_cast<T>(0.0f),
									   static_cast<T>(0.0f),
									   static_cast<T>(1.0f))),
				pDevice_(nullptr), pShader_(nullptr){}

	~_3DDevice()
	{

	}


public:
	void Init(Base_3DDevice <T>* const pDevice)
	{
		pDevice_ = pDevice;
	}

	void SetRenderMode(const _3D_FILL_MODE mode)
	{
		renderMode_ = mode;
	}

	void SetVertexBuffer(const std::vector <VertexIn <T>>& vertices)
	{
		vertices_ = vertices;
	}
	
	void SetIndexBuffer(const std::vector<unsigned int>& indices)
	{
		indices_ = indices;
	}


	void SetCameraPos(const Vector4 <T>& pos)
	{
		cameraPos_ = pos;
	}

	void SetShader(ShaderBase <T> * base)
	{
		pShader_ = base;
	}

	void DrawIndexed(const size_t indexCount, const size_t startIndexLocation, const size_t startVertexLocation)
	{
		Matrix <T> screenTransformMat;
		screenTransformMat = screenTransformMat.ScreenTransform(pDevice_->GetClientWidth(),
																pDevice_->GetClientHeight());
	
		for (size_t i = 0; i < indexCount / 3; ++i) {
			VertexIn <T> p1 = vertices_[startIndexLocation + indices_[3 * i]];
			VertexIn <T> p2 = vertices_[startIndexLocation + indices_[3 * i + 1]];
			VertexIn <T> p3 = vertices_[startIndexLocation + indices_[3 * i + 2]];

			// 背部消隐
			if (BackFaceCulling(p1, p2, p3) == false) {
				continue;
			}

			// 转换到齐次裁剪空间， 即投影后的坐标
			VertexOut <T>v1 = TransformToProj(p1);
			VertexOut <T>v2 = TransformToProj(p2);
			VertexOut <T>v3 = TransformToProj(p3);


			// 判断是否通过 cvv 裁剪
			if (Clip(v1) == false || Clip(v2) == false || Clip(v3) == false) {
				continue;
			}

			// 进行透视除法 转到cvv
			ToCVV(v1);
			ToCVV(v2);
			ToCVV(v3);
	
			// 将投影得到的坐标转化为屏幕坐标
			TransformToScreen(screenTransformMat, v1);
			TransformToScreen(screenTransformMat, v2);
			TransformToScreen(screenTransformMat, v3);

			DrawTriangle(v1, v2, v3);
		}
	}




private:
	void ToCVV(VertexOut <T>& v)
	{

		v.posH_.x_ /= v.posH_.w_;
		v.posH_.y_ /= v.posH_.w_;
		v.posH_.z_ /= v.posH_.w_;
		v.posH_.w_ = static_cast<T>(1.0f);
	}

	// 简单暴力的裁剪， 不在小盒子里，直接丢弃
	bool Clip(const VertexOut <T>& v)
	{

		if (v.posH_.x_ >= -v.posH_.w_ &&
			v.posH_.x_ <= v.posH_.w_ &&
			v.posH_.y_ >= -v.posH_.w_ &&
			v.posH_.y_ <= v.posH_.w_ &&
			v.posH_.z_ >= static_cast<T>(0.0f) &&
			v.posH_.z_ <= v.posH_.w_) {
			
			return true;
		}

		return false;
	}

	// 转到齐次裁剪空间， 相当于放在小盒子里。
	VertexOut <T> TransformToProj(const VertexIn <T>& v)
	{
		VertexOut <T> out = pShader_->VS(v);

		out.oneDivZ_ = static_cast<T>(1.0f) / out.posH_.w_;

		out.color_.x_ *= out.oneDivZ_;
		out.color_.y_ *= out.oneDivZ_;
		out.color_.z_ *= out.oneDivZ_;

		out.normal_.x_ *= out.oneDivZ_;
		out.normal_.y_ *= out.oneDivZ_;
		out.normal_.z_ *= out.oneDivZ_;

		out.tex_.x_ *= out.oneDivZ_;
		out.tex_.y_ *= out.oneDivZ_;

		return out;
	}

	// 转换到屏幕坐标
	void TransformToScreen(const Matrix <T>& m, VertexOut <T>& v)
	{

		v.posH_ = Vec4MutiMat(v.posH_, m);
	}

	// 背面消隐
	bool BackFaceCulling(const VertexIn <T>& v1, const VertexIn <T>& v2, const VertexIn <T>& v3)
	{
		if (renderMode_ == _3D_FILL_MODE::_3D_FILL_WIREFRAME) {
			return true;
		}

		else {
			Vector4 <T> vec1 = v2.pos_ - v1.pos_;
			Vector4 <T> vec2 = v3.pos_ - v2.pos_;

			// 顶点缓存中顺序为顺时针
			// 叉积得到的方向与右手系一致
			Vector4 <T> normal = vec1.Cross(vec2);

			Vector4 <T> viewDir = v1.pos_ - cameraPos_;
			if (normal.Dot(viewDir) < 0) {
				return true;
			}
		}

		return false;
	}

	void BresenhamDrawLine(int x1, int y1, int x2, int y2)
	{
		int dx = x2 - x1;
		int dy = y2 - y1;
		int stepx = 1;
		int stepy = 1;

		if (dx < 0) {
			stepx = -1;
			dx = abs(dx);
		}

		if (dy < 0) {
			stepy = -1;
			dy = abs(dy);
		}

		int deltaX = 2 * dx;
		int deltaY = 2 * dy;
		Vector4 <T> v(static_cast<T>(0.0f),
					  static_cast<T>(0.0f),
					  static_cast<T>(0.0f),
					  static_cast<T>(1.0f));

		if (dx > dy) {
			int error = deltaY - dx;


			for (int i = 0; i <= dx; ++i) {

				if (x1 >= 0 && x1 < pDevice_->GetClientWidth() &&
					y1 >= 0 && y1 < pDevice_->GetClientHeight()) {
					pDevice_->DrawPixel(x1, y1, v);
					
				}

				if (error >= 0) {
					error -= deltaX;
					y1 += stepy;
				}

				error += deltaY;
				x1 += stepx;
			}
		}

		else {
			int error = deltaX - dy;
			for (int i = 0; i <= dy; ++i) {
				if (x1 >= 0 && x1 < pDevice_->GetClientWidth() &&
					y1 >= 0 && y1 < pDevice_->GetClientWidth()) {
					pDevice_->DrawPixel(x1, y1, v);
				}

				if (error >= 0) {
					error -= deltaY;
					x1 += stepx;
				}

				error += deltaX;
				y1 += stepy;
			}
		}
	}

	void ScanLineFill(const VertexOut <T>& left, const VertexOut <T>& right, int yIndex)
	{
		T dx = right.posH_.x_ - left.posH_.x_;

		for (T x = left.posH_.x_; x <= right.posH_.x_; x += static_cast<T>(1.0f)) {
			// 四舍五入
			int xIndex = static_cast<int>(x + 0.5f);

			if (xIndex >= 0 && xIndex < pDevice_->GetClientWidth()) {
				// 插值系数
				T lerpFactor = 0;
				if (dx != 0) {
					lerpFactor = (x - left.posH_.x_) / dx;
				}

				// 深度测试
				// 1/z' 与 x' 和 y' 是线性关系的
				T oneDivZ = TpLerp(left.oneDivZ_, right.oneDivZ_, lerpFactor);

				if (oneDivZ >= pDevice_->GetZ(xIndex, yIndex)) {
					pDevice_->SetZ(xIndex, yIndex, oneDivZ);

					T w = static_cast<T>(1.0f) / oneDivZ;

					// 插值顶点 原先需要插值的信息均乘以 oneDivZ
					// 现在得到插值后的信息需要除以 oneDiZ 得到真实值
					VertexOut <T> out = left.Lerp(right, lerpFactor);



					out.posH_.y_ = static_cast<T>(yIndex);
					//out.tex_ *= w;
					out.normal_ *= w;
					out.color_ *= w;
				

					// 填充 像素点颜色
					pDevice_->DrawPixel(xIndex, yIndex, pShader_->PS(out));
					//assert(0);
				}
			}
		}
	}
	
	void DrawTriangle(const VertexOut <T>& v1, const VertexOut <T>& v2, const VertexOut <T>& v3)
	{
		if (renderMode_ == _3D_FILL_MODE::_3D_FILL_WIREFRAME) {
			BresenhamDrawLine(static_cast<int>(v1.posH_.x_), static_cast<T>(v1.posH_.y_), static_cast<T>(v2.posH_.x_), static_cast<T>(v2.posH_.y_));
			BresenhamDrawLine(static_cast<T>(v1.posH_.x_), static_cast<T>(v1.posH_.y_), static_cast<T>(v3.posH_.x_), static_cast<T>(v3.posH_.y_));
			BresenhamDrawLine(static_cast<T>(v2.posH_.x_), static_cast<T>(v2.posH_.y_), static_cast<T>(v3.posH_.x_), static_cast<T>(v3.posH_.y_));
		}

		else if (renderMode_ == _3D_FILL_MODE::_3D_FILL_SOLIDE) {
			TriangleRasterization(v1, v2, v3);

		}
	}

	void DrawTriangleTop(const VertexOut <T>& v1, const VertexOut <T>& v2, const VertexOut <T>& v3)
	{
		T dy = 0;	// 每次 y 增加一个像素
		for (T y = v1.posH_.y_; y <= v3.posH_.y_; y += static_cast<T>(1.0f)) {
			// 四舍五入
			int yIndex = static_cast<int>(y + static_cast<T>(0.5f));

			if (yIndex >= 0 && yIndex < pDevice_->GetClientHeight()) {
				T t = dy / (v3.posH_.y_ - v1.posH_.y_);

				// 插值左右顶点
				VertexOut <T> new1 = v1.Lerp(v3, t);
				VertexOut <T> new2 = v2.Lerp(v3, t);
				dy += static_cast<T>(1.0f);

				// 扫描线填充
				if (new1.posH_.x_ < new2.posH_.x_) {
					ScanLineFill(new1, new2, yIndex);
				}

				else {
					ScanLineFill(new2, new1, yIndex);
				}
			}
		}
	}

	void DrawTriangleBottom(const VertexOut <T>& v1, const VertexOut <T>& v2, const VertexOut <T>& v3)
	{
		T dy = 0;	// 每次 y 增加一个像素
		for (T y = v1.posH_.y_; y <= v2.posH_.y_; y += static_cast<T>(1.0f)) {
			// 四舍五入
			int yIndex = static_cast<int>(y + static_cast<T>(0.5f));

			if (yIndex >= 0 && yIndex < pDevice_->GetClientHeight()) {
				T t = dy / (v2.posH_.y_ - v1.posH_.y_);

				// 插值左右顶点
 				VertexOut <T> new1 = v1.Lerp(v2, t);
				VertexOut <T> new2 = v1.Lerp(v3, t);
				dy += static_cast<T>(1.0f);

				// 扫描线填充
				if (new1.posH_.x_ < new2.posH_.x_) {
					ScanLineFill(new1, new2, yIndex);
				}

				else {
					ScanLineFill(new2, new1, yIndex);
				}
			}
		}
	}

	// 光栅化 三角形
	void TriangleRasterization(const VertexOut <T>& v1, const VertexOut <T>& v2, const VertexOut <T>& v3)
	{
		// 判断是否是平底或者平顶三角形
		if (TpIsEqual(v1.posH_.y_, v2.posH_.y_)) {
			if (v1.posH_.y_ < v3.posH_.y_) {
				// 平顶
				DrawTriangleTop(v1, v2, v3);
			}

			else {
				// 平底
				DrawTriangleBottom(v3, v1, v2);
			}
		}

		else if (TpIsEqual(v1.posH_.y_, v3.posH_.y_)) {
			if (v1.posH_.y_ < v2.posH_.y_) {
				// 平顶
				DrawTriangleTop(v1, v3, v2);
			}

			else {
				// 平底
				DrawTriangleBottom(v2, v1, v3);
			}
		}

		else if (TpIsEqual(v2.posH_.y_, v3.posH_.y_)) {
			if (v2.posH_.y_ < v1.posH_.y_) {
				// 平顶
				DrawTriangleTop(v2, v3, v1);
			}

			else {
				// 平底
				DrawTriangleBottom(v1, v2, v3);
			}
		}

		// 一般三角形 将其分割成平底和平顶三角形
		else {
			std::vector<VertexOut <T>> vertices{ v1, v2, v3 };
			std::sort(vertices.begin(), vertices.end(), [](VertexOut <T> v1, VertexOut <T> v2) {
														return v1.posH_.y_ < v2.posH_.y_;
														});

			// 插值求中间点
			T middleX = (vertices[1].posH_.y_ - vertices[0].posH_.y_) * (vertices[2].posH_.x_ - vertices[0].posH_.x_) /
						(vertices[2].posH_.y_ - vertices[0].posH_.y_) + vertices[0].posH_.x_;

			T dy = vertices[1].posH_.y_ - vertices[0].posH_.y_;
			T t = dy / (vertices[2].posH_.y_ - vertices[0].posH_.y_);

			VertexOut <T> newMiddle = vertices[0].Lerp(vertices[2], t);
			newMiddle.posH_.x_ = middleX;
			newMiddle.posH_.y_ = vertices[1].posH_.y_;

			// 平顶
			DrawTriangleTop(vertices[1], newMiddle, vertices[2]);
			// 平底
			DrawTriangleBottom(vertices[0], vertices[1], newMiddle);
		}
	}



private:
	Base_3DDevice <T> *pDevice_;
	_3D_FILL_MODE renderMode_;
	std::vector<VertexIn <T>> vertices_;
	std::vector<unsigned int> indices_;
	ShaderBase <T> *pShader_;
	Vector4 <T> cameraPos_;
};

typedef _3DDevice <float> F3DDevice;
typedef _3DDevice <double> D3DDevice;

