//
// 用模板实现向量， 可以在实例化时选择 float 或是 double
// 2016/11/27
// by Chris
//

#pragma once


#include "Basic_Math.h"
#include <assert.h>

template <typename T>
class Vector2
{

public:
	Vector2() = default;

	Vector2(const T x, const T y)
	{
		x_ = x;
		y_ = y;
	}

	Vector2(const Vector2 <T> &vector2)
	{
		*this = vector2;
	}

	Vector2(const T value)
	{
		x_ = value;
		y_ = value;
	}


	// assignement operators
	Vector2& operator += (const Vector2 <T>& vector2)
	{
		x_ += vector2.x_;
		y_ += vector2.y_;

		return *this;
	}

	Vector2& operator -= (const Vector2 <T>& vector2)
	{
		x_ -= vector2.x_;
		y_ -= vector2.y_;

		return *this;
	}


	Vector2& operator *=(const T value)
	{
		x_ *= value;
		y_ *= value;

		return *this;
	}

	Vector2& operator *= (const Vector2 <T>& vector2)
	{
		x_ *= vector2.x_;
		y_ *= vector2.y_;

		return *this;
	}


	Vector2& operator /= (const Vector2 <T>& vector2)
	{

		assert(fabs(vector2.x_) >= ACCURACY_ERROR && 
			   fabs(vector2.y_) >= ACCURACY_ERROR &&
			   "in Vector2 operator /= function, cann't divisor by zero!");

		x_ /= vector2.x_;
		y_ /= vector2.y_;

		return *this;
	}


	// unary operators
	Vector2 <T> operator + () const
	{
		return *this;
	}

	Vector2 <T> operator - () const
	{
		Vector2 <T> result;
		result.x_ = -x_;
		result.y_ = -y_;
		return vector2;
	}


	// binary operators
	Vector2 operator + (const Vector2 <T>& vector2) const
	{
		Vector2 <T> result;
		result.x_ = x_ + vector2.x_;
		result.y_ = y_ + vector2.y_;

		return result;
	}

	Vector2 operator - (const Vector2 <T>& vector2) const
	{
		Vector2 <T> result;
		result.x_ = x_ - vector2.x_;
		result.y_ = y_ - vector2.y_;

		return result;
	}

	Vector2 operator * (const Vector2 <T>& vector2) const
	{
		Vector2 <T> result;
		result.x_ = x_ * vector2.x_;
		result.y_ = y_ * vector2.y_;

		return result;
	}

	Vector2 operator / (const Vector2 <T>& vector2) const
	{
		assert(fabs(vector2.x_) >= ACCURACY_ERROR && 
			  fabs(vector2.y_) >= ACCURACY_ERROR &&
			  "in Vector2 operator / function, cann't divisor by zero!");

		Vector2 <T> result;
		result.x_ = x_ / vector2.x_;
		result.y_ = y_ / vector2.y_;

		return result;
	}

	inline bool operator == (const Vector2 <T>& vector2) const
	{	
		return ((fabs(x_ - vector2.x_) <= ACCURACY_ERROR) && (fabs(y_ - vector2.y_) <= ACCURACY_ERROR));
	}

	inline bool operator != (const Vector2 <T>& vector2) const
	{
		return ((fabs(x_ - vector2.x_) >= ACCURACY_ERROR) || (fabs(y_ - vector2.y_) >= ACCURACY_ERROR));
	}


	// others
	inline T Dot(const Vector2 <T> &vector2) const
	{
		return x_ * vector2.x_ + y_ * vector2.y_;
	}

	/*
	Vector2 Cross(const Vector2 <T>& vector2) const
	{

	}
	*/

	inline Vector2 Normalize() const
	{
		assert(fabs(Length()) > ACCURACY_ERROR &&
			"Normalize function in Vector2, you cann't zero length as divisor!");

		T invLen = static_cast<T>(1.0f) / Length();
		Vector2 <T> result;

		result.x_ = x_ * invLen;
		result.y_ = y_ * invLen;

		return result;
	}

	inline Vector2 Minimize(const Vector2 <T>& vector2) const
	{
		Vector2 <T> result;
		result.x_ = TpMin(x_, vector2.x_);
		result.y_ = TpMin(y_, vector2.y_);
	
		return result;
	}

	inline Vector2 Maximize(const Vector2 <T>& vector2) const
	{
		Vector2 <T> result;
		result.x_ = TpMax(x_, vector2.x_);
		result.y_ = TpMax(y_, vector2.y_);
		
		return result;
	}

	inline Vector2 Lerp(const Vector2 <T>& vector2, T s) const
	{
		Vector2 result;
		result.x_ = x_ + s * vector2.x_;
		result.y_ = y_ + s * vector2.y_;
		
		return result;
	}

	inline T Length() const
	{
		return static_cast<T>(sqrt(LengthSq()));
	}

	inline T LengthSq() const
	{
		return x_ * x_ + y_ * y_;
	}

public:
	T x_, y_;
};


template <typename T>
class Vector3
{
public:
	Vector3() = default;
	Vector3(const T value)
	{
		x_ = value;
		y_ = value;
		z_ = value;
	}

	Vector3(const T x, const T y, const T z)
	{
		x_ = x;
		y_ = y;
		z_ = z;
	}

	Vector3(const Vector3 <T>& vector3)
	{
		x_ = vector3.x_;
		y_ = vector3.y_;
		z_ = vector3.z_;
	}



	// assignment operators
	Vector3& operator += (const Vector3 <T>& vector3)
	{
		x_ += vector3.x_;
		y_ += vector3.y_;
		z_ += vector3.z_;

		return *this;
	}

	Vector3& operator -= (const Vector3 <T>& vector3)
	{
		x_ -= vector3.x_;
		y_ -= vector3.y_;
		z_ -= vector3.z_;

		return *this;
	}

	Vector3& operator *= (const Vector3 <T>& vector3)
	{
		x_ *= vector3.x_;
		y_ *= vector3.y_;
		z_ *= vector3.z_;

		return *this;
	}


	Vector3& operator *= (const T value)
	{
		x_ *= value;
		y_ *= value;
		z_ *= value;

		return *this;
	}

	Vector3& operator /= (const Vector3 <T>& vector3)
	{
		assert(fabs(vector3.x_) > ACCURACY_ERROR &&
			   fabs(vector3.y_) > ACCURACY_ERROR &&
			   fabs(vector3.z_) > ACCURACY_ERROR &&
			   "operator /= function in Vector3, you cann't zero as divisor!");

		x_ /= vector3.x_;
		y_ /= vector3.y_;
		z_ /= vector3.z_;

		return *this;
	}



	//unary operators
	Vector3 <T> operator - () const
	{
		Vector3 <T> result;
		result.x_ = -x_;
		result.y_ = -y_;
		result.z_ = -z_;

		return result;
	}

	Vector3 <T> operator + () const
	{
		return *this;
	}




	// binary operators
	Vector3 operator + (const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = x_ + vector3.x_;
		result.y_ = y_ + vector3.y_;
		result.z_ = z_ + vector3.z_;

		return result;
	}

	Vector3 operator - (const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = x_ - vector3.x_;
		result.y_ = y_ - vector3.y_;
		result.z_ = z_ - vector3.z_;

		return result;
	}
	
	inline Vector3 operator * (const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = x_ * vector3.x_;
		result.y_ = y_ * vector3.y_;
		result.z_ = z_ * vector3.z_;

		return result;
	}


	inline Vector3 operator / (const Vector3 <T>& vector3) const
	{
		assert(fabs(vector3.x_) > ACCURACY_ERROR &&
			   fabs(vector3.y_) > ACCURACY_ERROR &&
			   fabs(vector3.z_) > ACCURACY_ERROR &&
			   "operator / function in Vector3, you cann't zero as divisor!");

		Vector3 <T> result;
		result.x_ = x_ / vector3.x_;
		result.y_ = y_ / vector3.y_;
		result.z_ = z_ / vector3.z_;

		return result;
	}

	inline bool operator == (const Vector3 <T>& vector3) const
	{
		return ((fabs(x_ - vector3.x_) <= ACCURACY_ERROR) &&
			    (fabs(y_ - vector3.y_) <= ACCURACY_ERROR) &&
				(fabs(z_ - vector3.z_) <= ACCURACY_ERROR));
	}

	inline bool operator != (const Vector3 <T>& vector3) const
	{
		return ((fabs(x_ - vector3.x_) > ACCURACY_ERROR) &&
				(fabs(y_ - vector3.y_) > ACCURACY_ERROR) &&
				(fabs(z_ - vector3.z_) > ACCURACY_ERROR));
	}



	// others
	inline Vector3 Normalize() const
	{
		assert(fabs(Length()) > ACCURACY_ERROR &&
			  "Normalize function in Vector3, you cann't zero length as divisor!");

		T invLen = static_cast<T>(1.0f) / Length();
		Vector3 <T> result;
		result.x_ = x_ * invLen;
		result.y_ = y_ * invLen;
		result.z_ = z_ * invLen;

		return result;
	}

	inline Vector3 Maximize(const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = TpMax(x_, vector3.x_);
		result.y_ = TpMax(y_, vector3.y_);
		result.z_ = TpMax(z_, vector3.z_);

		return result;
	}

	inline Vector3 Minimize(const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = TpMin(x_, vector3.x_);
		result.y_ = TpMin(y_, vector3.y_);
		result.z_ = TpMin(z_, vector3.z_);

		return result;
	}

	T Dot(const Vector3 <T>& vector3) const
	{
		return x_ * vector3.x_ + y_ * vector3.y_ + z_ * vector3.z_;
	}

	Vector3 Cross(const Vector3 <T>& vector3) const
	{
		Vector3 <T> result;
		result.x_ = y_ * vector3.z_ - z_ * vector3.y_;
		result.y_ = x_ * vector3.z_ - z_ * vector3.x_;
		result.z_ = x_ * vector3.y_ - y_ * vector3.x_;

		return result;
	}

	inline T Length() const
	{
		return static_cast<T>(sqrt(LengthSq()));
	}

	inline T LengthSq() const
	{
		return x_ * x_ + y_ * y_ + z_ * z_;
	}

	inline Vector3 Lerp(const Vector3 <T>& vector3, const T s) const
	{
		Vector3 <T> result;
		result.x_ = x_ + s * vector3.x_;
		result.y_ = y_ + s * vector3.y_;
		result.z_ = z_ + s * vector3.z_;

		return result;
	}


public:
	T x_, y_, z_;
};



template <typename T>
class Vector4
{
public:
	Vector4() = default;
	Vector4(T value)
	{
		x_ = value;
		y_ = value;
		z_ = value;
		w_ = static_cast<T>(0.0f);
	}

	Vector4(const Vector4 <T>& vector4)
	{
		x_ = vector4.x_;
		y_ = vector4.y_;
		z_ = vector4.z_;
		w_ = vector4.w_;
	}

	Vector4(const T x, const T y, const T z, const T w = static_cast<T>(0.0f))
	{
		x_ = x;
		y_ = y;
		z_ = z;
		w_ = w;
	}

	Vector4(const class Vector3 <T>& vector3, const T w)
	{
		x_ = vector3.x_;
		y_ = vector3.y_;
		z_ = vector3.z_;
		w_ = w;
	}



	// assignment operators
	Vector4& operator += (const Vector4 <T>& vector4)
	{
		x_ += vector4.x_;
		y_ += vector4.y_;
		z_ += vector4.z_;
		w_ = static_cast<T>(0.0f);

		return *this;
	}

	Vector4& operator -= (const Vector4 <T>& vector4)
	{
		x_ -= vector4.x_;
		y_ -= vector4.y_;
		z_ -= vector4.z_;
		w_ = static_cast<T>(0.0f);

		return *this;
	}

	Vector4& operator *= (const Vector4 <T>& vector4)
	{
		x_ *= vector4.x_;
		y_ *= vector4.y_;
		z_ *= vector4.z_;
		w_ *= vector4.w_;

		return *this;
	}

	Vector4& operator *=(const T value)
	{
		x_ *= value;
		y_ *= value;
		z_ *= value;

		return *this;
	}

	Vector4& operator /= (const Vector4 <T>& vector4)
	{
		assert((fabs(vector4.x_) > ACCURACY_ERROR) &&
			   (fabs(vector4.y_) > ACCURACY_ERROR) &&
			   (fabs(vector4.z_) > ACCURACY_ERROR) &&
			   "Operator /= function in Vector4, you cann't zero as divisor!");

		x_ /= vector4.x_;
		y_ /= vector4.y_;
		z_ /= vector4.z_;
		w_ = static_cast<T>(0.0f);

		return *this;
	}


	// unary operators
	Vector4 operator - () const
	{
		Vector4 <T> result;
		result.x_ = -x_;
		result.y_ = -y_;
		result.z_ = -z_;
		result.w_ = w_;

		return result;
	}

	Vector4 operator + () const
	{
		return *this;
	}

	

	// binary operators
	Vector4 operator + (const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = x_ + vector4.x_;
		result.y_ = y_ + vector4.y_;
		result.z_ = z_ + vector4.z_;
		result.w_ = static_cast<T>(0.0f);

		return result;
	}

	Vector4 operator - (const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = x_ - vector4.x_;
		result.y_ = y_ - vector4.y_;
		result.z_ = z_ - vector4.z_;
		result.w_ = static_cast<T>(0.0f);

		return result;
	}

	inline Vector4 operator * (const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = x_ * vector4.x_;
		result.y_ = y_ * vector4.y_;
		result.z_ = z_ * vector4.z_;
		result.w_ = w_ * vector4.w_;

		return result;
	}

	
	Vector4 operator * (T value) const
	{
		Vector4 <T> result;
		result.x_ = x_ * value;
		result.y_ = y_ * value;
		result.z_ = z_ * value;
		result.w_ = w_;

		return result;
	}

	Vector4 operator / (const Vector4 <T>& vector4) const
	{
		assert((fabs(vector4.x_) > ACCURACY_ERROR) &&
				(fabs(vector4.y_) > ACCURACY_ERROR) &&
				(fabs(vector4.z_) > ACCURACY_ERROR) &&
				"operator / function in Vector4, you cann't zero as divisor!");

		Vector4 <T> result;
		result.x_ = x_ / vector4.x_;
		result.y_ = y_ / vector4.y_;
		result.z_ = z_ / vector4.z_;
		result.w_ = w_;

		return result;
	}

	bool operator == (const Vector4 <T>& vector4) const
	{
		return ((fabs(x_ - vector4.x_) <= ACCURACY_ERROR) &&
				(fabs(y_ - vector4.y_) <= ACCURACY_ERROR) &&
				(fabs(z_ - vector4.z_) <= ACCURACY_ERROR) &&
			    (fabs(w_ - vector4.w_) <= ACCURACY_ERROR));
	}

	bool operator != (const Vector4 <T>& vector4) const
	{
		return ((fabs(x_ - vector4.x_) > ACCURACY_ERROR) || 
			    (fabs(y_ - vector4.y_) > ACCURACY_ERROR) ||
			    (fabs(z_ - vector4.z_) > ACCURACY_ERROR) ||
			    (fabs(w_ - vector4.w_) > ACCURACY_ERROR));
	}


	// others
	inline Vector4 Normalize() const
	{
		assert(fabs(Length()) > ACCURACY_ERROR &&
			"Normalize function in Vector3, you cann't zero length as divisor!");

		T invLen = static_cast<T>(1.0f) / Length();
		Vector4 <T> result;
		result.x_ = x_ * invLen;
		result.y_ = y_ * invLen;
		result.z_ = z_ * invLen;
		result.w_ = w_;
		return result;
	}

	inline T Length() const
	{
		return static_cast<T>(sqrt(LengthSq()));
	}

	inline T LengthSq() const
	{
		return x_ * x_ + y_ * y_ + z_* z_;
	}

	inline Vector4 Minimize(const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = TpMin(x_, vector4.x_);
		result.y_ = TpMin(y_, vector4.y_);
		result.z_ = TpMin(z_, vector4.z_);
		result.w_ = w_;

		return result;
	}

	inline Vector4 Maximize(const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = TpMax(x_, vector4.x_);
		result.y_ = TpMax(y_, vector4.y_);
		result.z_ = TpMax(z_, vector4.z_);
		result.w_ = w_;

		return result;
	}

	inline T Dot(const Vector4 <T>& vector4) const
	{
		return (x_ * vector4.x_ +
				y_ * vector4.y_ +
				z_ * vector4.z_);
	}

	inline Vector4 Cross(const Vector4 <T>& vector4) const
	{
		Vector4 <T> result;
		result.x_ = y_ * vector4.z_ - z_ * vector4.y_;
		result.y_ = z_ * vector4.x_ - x_ * vector4.z_;
		result.z_ = x_ * vector4.y_ - y_ * vector4.x_;
		result.w_ = static_cast<T>(0.0f);

		return result;
	}

	inline Vector4 Lerp(const Vector4 <T>& vector4, T s) const
	{
		Vector4 <T> result;
		result.x_ = x_ + s * vector4.x_;
		result.y_ = y_ + s * vector4.y_;
		result.z_ = z_ + s * vector4.z_;
		result.w_ = static_cast<T>(0.0f);

		return result;
	}

public:
	T x_, y_, z_, w_;
};




