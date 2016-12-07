#pragma once

#include "Basic_Math.h"
#include "Vector.h"
#include "Matrix.h"



template <typename T>
inline unsigned int ColorToUInt(const Vector3 <T>& color3)
{
	unsigned char red = static_cast<unsigned char>(255 * color3.x_);
	unsigned char green = static_cast<unsigned char>(255 * color3.y_);
	unsigned char blue = static_cast<unsigned char>(255 * color3.z_);

	return (static_cast<unsigned int>(blue) |
		    static_cast<unsigned int>(green) << 8 |
		    static_cast<unsigned int>(red) << 16);
}



template <typename T>
inline unsigned int ColorToUInt(const Vector4 <T>& color4)
{
	unsigned char red = static_cast<unsigned char>(255 * color4.x_);
	unsigned char green = static_cast<unsigned char>(255 * color4.y_);
	unsigned char blue = static_cast<unsigned char>(255 * color4.z_);
	unsigned char alpha = static_cast<unsigned char>(255 * color4.w_);

	return (static_cast<unsigned int>(blue) |
		static_cast<unsigned int>(green) << 8 |
		static_cast<unsigned int>(red) << 16);
			//static_cast<unsigned int>(alpha) << 24);
}



template <typename T>
inline T Reflect(const T& I, const T& N)
{
	auto tmp = static_cast<decltype(I.x_)>(2.0f) * I.Dot(N);
	return I - (N * tmp);
}

 
template <typename T>
inline T TpLerp(const T a, const T b, const T factor)
{
	return a + b * factor;
}


template <typename T>
inline T ConvertToRadians(T d)
{
	return d * static_cast<T>(PI / 180.0);
}


template <typename T>
inline Vector4 <T> Vec4MutiMat(const Vector4 <T> &Vec, const Matrix <T>& matrix)
{
	Vector4 <T> result;
	result.x_ = Vec.x_ * matrix._11 + Vec.y_ * matrix._21 +
		Vec.z_ * matrix._31 + Vec.w_ * matrix._41;

	result.y_ = Vec.x_ * matrix._12 + Vec.y_ * matrix._22 +
		Vec.z_ * matrix._32 + Vec.w_ * matrix._42;

	result.z_ = Vec.x_ * matrix._13 + Vec.y_ * matrix._23 +
		Vec.z_ * matrix._33 + Vec.w_ * matrix._43;

	result.w_ = Vec.x_ * matrix._14 + Vec.y_ * matrix._24 +
		Vec.z_ * matrix._34 + Vec.w_ * matrix._44;

	return result;
}


template <typename T>
inline T Clamp(T x, T min, T max)
{
	if (x <= min) {
		return min;
	}

	else if (x >= max) {
		return max;
	}

	return x;
}



typedef class Matrix <float> FMatrix;
typedef class Matrix <double> DMatrix;

typedef class Vector2 <float> FVector2;
typedef class Vector2 <double> DVector2;

typedef class Vector3 <float> FVector3;
typedef class Vector3 <double> DVector3;

typedef class Vector4 <float> FVector4;
typedef class Vector4 <double> DVector4;