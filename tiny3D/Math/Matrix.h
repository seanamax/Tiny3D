#pragma once

#include <cstring>
#include <cstdlib>
#include <cmath>
#include "Vector.h"
#include "Basic_Math.h"


template <typename T>
class Matrix
{
public:
	Matrix() = default;

	Matrix(const Matrix <T>& matrix)
	{
		memcpy(m, matrix.m, sizeof(m));
	}

	Matrix(T v_11, T v_12, T v_13, T v_14,
		   T v_21, T v_22, T v_23, T v_24,
		   T v_31, T v_32, T v_33, T v_34,
		   T v_41, T v_42, T v_43, T v_44
		) {
		
		_11 = v_11;
		_12 = v_12;
		_13 = v_13;
		_14 = v_14;
		
		_21 = v_21;
		_22 = v_22;
		_23 = v_23;
		_24 = v_24;

		_31 = v_31;
		_32 = v_32;
		_33 = v_33;
		_34 = v_34;

		_41 = v_41;
		_42 = v_42;
		_43 = v_43;
		_44 = v_44;

	}

	// access grant
	T operator () (const size_t row, const size_t col) const
	{
		return m[row][col];
	}

	

	// assignment operators
	Matrix& operator *= (const Matrix <T>& matrix)
	{
		Vector4 <T> result;
		
		result.x_ = _11 * matrix._11 + _12 * matrix._21 +
					_13 * matrix._31 + _14 * matrix._41;

		result.y_ = _11 * matrix._12 + _12 * matrix._22 +
					_13 * matrix._32 + _14 * matrix._42;

		result.z_ = _11 * matrix._13 + _12 * matrix._23 +
					_13 * matrix._33 + _14 * matrix._43;


		result.w_ = _11 * matrix._14 + _12 * matrix._24 + 
					_13 * matrix._34 + _14 * matrix._44;


		_11 = result.x_;
		_12 = result.y_;
		_13 = result.z_;
		_14 = result.w_;



		result.x_ = _21 * matrix._11 + _22 * matrix._21 +
			_23 * matrix._31 + _24 * matrix._41;

		result.y_ = _21 * matrix._12 + _22 * matrix._22 +
			_23 * matrix._32 + _24 * matrix._42;

		result.z_ = _21 * matrix._13 + _22 * matrix._23 +
			_23 * matrix._33 + _24 * matrix._43;


		result.w_ = _21 * matrix._14 + _22 * matrix._24 +
			_23 * matrix._34 + _24 * matrix._44;


		_21 = result.x_;
		_22 = result.y_;
		_23 = result.z_;
		_24 = result.w_;



		result.x_ = _31 * matrix._11 + _32 * matrix._21 +
			_33 * matrix._31 + _34 * matrix._41;

		result.y_ = _31 * matrix._12 + _32 * matrix._22 +
			_33 * matrix._32 + _34 * matrix._42;

		result.z_ = _31 * matrix._13 + _32 * matrix._23 +
			_33 * matrix._33 + _34 * matrix._43;


		result.w_ = _31 * matrix._14 + _32 * matrix._24 +
			_33 * matrix._34 + _34 * matrix._44;


		_31 = result.x_;
		_32 = result.y_;
		_33 = result.z_;
		_34 = result.w_;



		result.x_ = _41 * matrix._11 + _42 * matrix._21 +
			_43 * matrix._31 + _44 * matrix._41;

		result.y_ = _41 * matrix._12 + _42 * matrix._22 +
			_43 * matrix._32 + _44 * matrix._42;

		result.z_ = _41 * matrix._13 + _42 * matrix._23 +
			_43 * matrix._33 + _44 * matrix._43;


		result.w_ = _41 * matrix._14 + _42 * matrix._24 +
			_43 * matrix._34 + _44 * matrix._44;


		_41 = result.x_;
		_42 = result.y_;
		_43 = result.z_;
		_44 = result.w_;


		return *this;
	}

	// 用两个 for 嵌套当然可以， 只是效率会低些。
	// 直接手工 展开， 毕竟也不多
	Matrix& operator += (const Matrix <T>& matrix)
	{
		_11 += matrix._11;
		_12 += matrix._12;
		_13 += matrix._13;
		_14 += matrix._14;
		

		_21 += matrix._21;
		_22 += matrix._22;
		_23 += matrix._23;
		_24 += matrix._24;


		_31 += matrix._31;
		_32 += matrix._32;
		_33 += matrix._33;
		_34 += matrix._34;


		_41 += matrix._41;
		_42 += matrix._42;
		_43 += matrix._43;
		_44 += matrix._44;

		return *this;
	}

	Matrix& operator -= (const Matrix <T>& matrix)
	{
		_11 -= matrix._11;
		_12 -= matrix._12;
		_13 -= matrix._13;
		_14 -= matrix._14;


		_21 -= matrix._21;
		_22 -= matrix._22;
		_23 -= matrix._23;
		_24 -= matrix._24;


		_31 -= matrix._31;
		_32 -= matrix._32;
		_33 -= matrix._33;
		_34 -= matrix._34;


		_41 -= matrix._41;
		_42 -= matrix._42;
		_43 -= matrix._43;
		_44 -= matrix._44;

		return *this;
	}

	Matrix& operator *= (const T value)
	{
		_11 *= value;
		_12 *= value;
		_13 *= value;
		_14 *= value;

		_21 *= value;
		_22 *= value;
		_23 *= value;
		_24 *= value;

		_31 *= value;
		_32 *= value;
		_33 *= value;
		_34 *= value;

		_41 *= value;
		_42 *= value;
		_43 *= value;
		_44 *= value;

		return *this;
	}

	
	Matrix& operator /= (const T value)
	{
		_11 /= value;
		_12 /= value;
		_13 /= value;
		_14 /= value;

		_21 /= value;
		_22 /= value;
		_23 /= value;
		_24 /= value;

		_31 /= value;
		_32 /= value;
		_33 /= value;
		_34 /= value;

		_41 /= value;
		_42 /= value;
		_43 /= value;
		_44 /= value;

		return *this;
	}

	

	// unary operators
	Matrix operator + () const
	{
		return *this;
	}

	Matrix operator - () const
	{
		Matrix <T> result;
		result._11 = -_11;
		result._12 = -_12;
		result._13 = -_13;
		result._14 = -_14;
		
		result._21 = -_21;
		result._22 = -_22;
		result._23 = -_23;
		result._24 = -_24;
		
		result._31 = -_31;
		result._32 = -_32;
		result._33 = -_33;
		result._34 = -_34;

		result._41 = -_41;
		result._42 = -_42;
		result._43 = -_43;
		result._44 = -_44;

		return result;
	}

	
	
	// binary operators
	Matrix operator * (const Matrix <T>& matrix) const
	{
		Matrix <T> result;

		result._11 = _11 * matrix._11 + _12 * matrix._21 +
			_13 * matrix._31 + _14 * matrix._41;

		result._12 = _11 * matrix._12 + _12 * matrix._22 +
			_13 * matrix._32 + _14 * matrix._42;

		result._13 = _11 * matrix._13 + _12 * matrix._23 +
			_13 * matrix._33 + _14 * matrix._43;


		result._14 = _11 * matrix._14 + _12 * matrix._24 +
			_13 * matrix._34 + _14 * matrix._44;



		result._21 = _21 * matrix._11 + _22 * matrix._21 +
			_23 * matrix._31 + _24 * matrix._41;

		result._22 = _21 * matrix._12 + _22 * matrix._22 +
			_23 * matrix._32 + _24 * matrix._42;

		result._23 = _21 * matrix._13 + _22 * matrix._23 +
			_23 * matrix._33 + _24 * matrix._43;


		result._24 = _21 * matrix._14 + _22 * matrix._24 +
			_23 * matrix._34 + _24 * matrix._44;



		result._31 = _31 * matrix._11 + _32 * matrix._21 +
			_33 * matrix._31 + _34 * matrix._41;

		result._32 = _31 * matrix._12 + _32 * matrix._22 +
			_33 * matrix._32 + _34 * matrix._42;

		result._33 = _31 * matrix._13 + _32 * matrix._23 +
			_33 * matrix._33 + _34 * matrix._43;


		result._34 = _31 * matrix._14 + _32 * matrix._24 +
			_33 * matrix._34 + _34 * matrix._44;



		result._41 = _41 * matrix._11 + _42 * matrix._21 +
			_43 * matrix._31 + _44 * matrix._41;

		result._42 = _41 * matrix._12 + _42 * matrix._22 +
			_43 * matrix._32 + _44 * matrix._42;

		result._43 = _41 * matrix._13 + _42 * matrix._23 +
			_43 * matrix._33 + _44 * matrix._43;


		result._44 = _41 * matrix._14 + _42 * matrix._24 +
			_43 * matrix._34 + _44 * matrix._44;


		return result;
	}

	Matrix operator + (const Matrix <T>& matrix) const
	{
		Matrix <T> result;

		result._11 = _11 + matrix._11;
		result._12 = _12 + matrix._12;
		result._13 = _13 + matrix._13;
		result._14 = _14 + matrix._14;


		result._21 = _21 + matrix._21;
		result._22 = _22 + matrix._22;
		result._23 = _23 + matrix._23;
		result._24 = _24 + matrix._24;


		result._31 = _31 + matrix._31;
		result._32 = _32 + matrix._32;
		result._33 = _33 + matrix._33;
		result._34 = _34 + matrix._34;


		result._41 = _41 + matrix._41;
		result._42 = _42 + matrix._42;
		result._43 = _43 + matrix._43;
		result._44 = _44 + matrix._44;

		return result; 
	}

	Matrix operator - (const Matrix <T>& matrix) const
	{
		Matrix <T> result;

		result._11 = _11 - matrix._11;
		result._12 = _12 - matrix._12;
		result._13 = _13 - matrix._13;
		result._14 = _14 - matrix._14;


		result._21 = _21 - matrix._21;
		result._22 = _22 - matrix._22;
		result._23 = _23 - matrix._23;
		result._24 = _24 - matrix._24;


		result._31 = _31 - matrix._31;
		result._32 = _32 - matrix._32;
		result._33 = _33 - matrix._33;
		result._34 = _34 - matrix._34;


		result._41 = _41 - matrix._41;
		result._42 = _42 - matrix._42;
		result._43 = _43 - matrix._43;
		result._44 = _44 - matrix._44;

		return result;
	}

	Matrix operator * (const T value) const
	{
		Matrix <T> result;

		result._11 = _11 * value;
		result._12 = _12 * value;
		result._13 = _13 * value;
		result._14 = _14 * value;


		result._21 = _21 * value;
		result._22 = _22 * value;
		result._23 = _23 * value;
		result._24 = _24 * value;


		result._31 = _31 * value;
		result._32 = _32 * value;
		result._33 = _33 * value;
		result._34 = _34 * value;


		result._41 = _41 * value;
		result._42 = _42 * value;
		result._43 = _43 * value;
		result._44 = _44 * value;

		return result;
	}

	Matrix operator / (const T value) const
	{
		assert(fabs(value) >= ACCURACY_ERROR &&
			"you cann't make value as divisor!");


		Matrix <T> result;
		result._11 = _11 / value;
		result._12 = _12 / value;
		result._13 = _13 / value;
		result._14 = _14 / value;


		result._21 = _21 / value;
		result._22 = _22 / value;
		result._23 = _23 / value;
		result._24 = _24 / value;


		result._31 = _31 / value;
		result._32 = _32 / value;
		result._33 = _33 / value;
		result._34 = _34 / value;


		result._41 = _41 / value;
		result._42 = _42 / value;
		result._43 = _43 / value;
		result._44 = _44 / value;

		return result;
	}


	bool operator == (const Matrix <T>& matrix) const
	{
		return ((fabs(matrix._11 - _11) <= ACCURACY_ERROR) &&
				(fabs(matrix._12 - _12) <= ACCURACY_ERROR) &&
				(fabs(matrix._13 - _13) <= ACCURACY_ERROR) &&
				(fabs(matrix._14 - _14) <= ACCURACY_ERROR) &&
			
				(fabs(matrix._21 - _21) <= ACCURACY_ERROR) &&
				(fabs(matrix._22 - _22) <= ACCURACY_ERROR) &&
				(fabs(matrix._23 - _23) <= ACCURACY_ERROR) &&
				(fabs(matrix._24 - _24) <= ACCURACY_ERROR) &&
				
				(fabs(matrix._31 - _31) <= ACCURACY_ERROR) &&
				(fabs(matrix._32 - _32) <= ACCURACY_ERROR) &&
				(fabs(matrix._33 - _33) <= ACCURACY_ERROR) &&
				(fabs(matrix._34 - _34) <= ACCURACY_ERROR) &&
			
				(fabs(matrix._41 - _41) <= ACCURACY_ERROR) &&
				(fabs(matrix._42 - _42) <= ACCURACY_ERROR) &&
				(fabs(matrix._43 - _43) <= ACCURACY_ERROR) &&
				(fabs(matrix._44 - _44) <= ACCURACY_ERROR));
		
	}

	bool operator != (const Matrix <T>& matrix) const
	{
		return ((fabs(matrix._11 - _11) > ACCURACY_ERROR) ||
				(fabs(matrix._12 - _12) > ACCURACY_ERROR) ||
				(fabs(matrix._13 - _13) > ACCURACY_ERROR) ||
				(fabs(matrix._14 - _14) > ACCURACY_ERROR) ||

				(fabs(matrix._21 - _21) > ACCURACY_ERROR) ||
				(fabs(matrix._22 - _22) > ACCURACY_ERROR) ||
				(fabs(matrix._23 - _23) > ACCURACY_ERROR) ||
				(fabs(matrix._24 - _24) > ACCURACY_ERROR) ||

				(fabs(matrix._31 - _31) > ACCURACY_ERROR) ||
				(fabs(matrix._32 - _32) > ACCURACY_ERROR) ||
				(fabs(matrix._33 - _33) > ACCURACY_ERROR) ||
				(fabs(matrix._34 - _34) > ACCURACY_ERROR) ||

				(fabs(matrix._41 - _41) > ACCURACY_ERROR) ||
				(fabs(matrix._42 - _42) > ACCURACY_ERROR) ||
				(fabs(matrix._43 - _43) > ACCURACY_ERROR) ||
				(fabs(matrix._44 - _44) > ACCURACY_ERROR));
	}

	// friend function
	friend Matrix operator * (const float value, const Matrix <T>& matrix)
	{
		Matrix <T> result;

		result._11 = matrix._11 * value;
		result._12 = matrix._12 * value;
		result._13 = matrix._13 * value;
		result._14 = matrix._14 * value;


		result._21 = matrix._21 * value;
		result._22 = matrix._22 * value;
		result._23 = matrix._23 * value;
		result._24 = matrix._24 * value;


		result._31 = matrix._31 * value;
		result._32 = matrix._32 * value;
		result._33 = matrix._33 * value;
		result._34 = matrix._34 * value;


		result._41 = matrix._41 * value;
		result._42 = matrix._42 * value;
		result._43 = matrix._43 * value;
		result._44 = matrix._44 * value;

		return result;
	}


	
	// others
	
	Matrix Transpose() const
	{
		Matrix <T> result;

		result._11 = _11;
		result._12 = _21;
		result._13 = _31;
		result._14 = _41;

		result._21 = _12;
		result._22 = _22;
		result._23 = _32;
		result._24 = _42;

		result._31 = _13;
		result._32 = _23;
		result._33 = _33;
		result._34 = _43;

		result._41 = _14;
		result._42 = _24;
		result._43 = _34;
		result._44 = _44;

		return result;
	}

	Matrix Identity() const
	{
		Matrix <T> result;

		result._11 = static_cast<T>(1.0f);
		result._12 = static_cast<T>(0.0f);
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = static_cast<T>(1.0f);
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);
		
		result._31 = static_cast<T>(0.0f);
		result._32 = static_cast<T>(0.0f);
		result._33 = static_cast<T>(1.0f);
		result._34 = static_cast<T>(0.0f);

		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	
	Matrix SetZero() const
	{
		Matrix <T> result;
		memset(result.m, 0, sizeof(result.m));

		/*
		result._11 = static_cast<T>(0.0f);
		result._12 = static_cast<T>(0.0f);
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = static_cast<T>(0.0f);
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);

		result._31 = static_cast<T>(0.0f);
		result._32 = static_cast<T>(0.0f);
		result._33 = static_cast<T>(0.0f);
		result._34 = static_cast<T>(0.0f);

		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(0.0f);

		*/
		return result;
	}

	// 余子式
	inline T Cofactor(T v_11, T v_12, T v_13,
					  T v_21, T v_22, T v_23,
					  T v_31, T v_32, T v_33) const
	{
		return ((v_11 * v_22 * v_33) +
				(v_12 * v_23 * v_31) +
				(v_13 * v_32 * v_21) -
				(v_31 * v_22 * v_13) -
				(v_32 * v_23 * v_11) -
				(v_33 * v_12 * v_21));
	}

	inline T Det() const
	{
		return (_11 * Cofactor(_22, _23, _24,
							   _32, _33, _34,
							   _42, _43, _44) 

			  - _12 * Cofactor(_21, _23, _24,
							   _31, _33, _34,
							   _41, _43, _44) 

			  + _13 * Cofactor(_21, _22, _24,
							   _31, _32, _34,
							   _41, _42, _44)
				
			  - _14 * Cofactor(_21, _22, _23,
							   _31, _32, _33,
							   _41, _42, _43) 
				);

	}

	
	// 伴随矩阵
	inline Matrix <T> Ajoint() const
	{
		Matrix <T> result;

		result._11 = Cofactor(_22, _23, _24, _32, _33, _34, _42, _43, _44);
		result._21 = - Cofactor(_21, _23, _24, _31, _33, _34, _41, _43, _44);
		result._31 = Cofactor(_21, _22, _24, _31, _32, _34, _41, _42, _44);
		result._41 = - Cofactor(_21, _22, _23, _31, _32, _33, _41, _42, _43);
		
		result._12 = - Cofactor(_12, _13, _14, _32, _33, _34, _42, _43, _44);
		result._22 = Cofactor(_11, _13, _14, _31, _33, _34, _41, _43, _44);
		result._32 = - Cofactor(_11, _12, _14, _31, _32, _34, _41, _42, _44);
		result._42 = Cofactor(_11, _12, _13, _31, _32, _33, _41, _42, _43);
		
		result._13 = Cofactor(_12, _13, _14, _22, _23, _24, _42, _43, _44);
		result._23 = - Cofactor(_11, _13, _14, _21, _23, _24, _41, _43, _44);
		result._33 = Cofactor(_11, _12, _14, _21, _22, _24, _41, _42, _44);
		result._43 = - Cofactor(_11, _12, _13, _21, _22, _23, _41, _42, _43);
		
		result._14 = - Cofactor(_12, _13, _14, _22, _23, _24, _32, _33, _34);
		result._24 = Cofactor(_11, _13, _14, _21, _23, _24, _31, _33, _34);
		result._34 = - Cofactor(_11, _12, _14, _21, _22, _24, _31, _32, _34);
		result._44 = Cofactor(_11, _12, _13, _21, _22, _23, _31, _32, _33);

		return result;
	}

	
	inline Matrix Inverse() const
	{
		return Ajoint() / Det();
	}

	
	inline Matrix Scaling(T scaleX, T scaleY, T scaleZ) const
	{
		Matrix <T> result;
		result._11 = scaleX;
		result._12 = static_cast<T>(0.0f);
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = scaleY;
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);

		result._31 = static_cast<T>(0.0f);
		result._32 = static_cast<T>(0.0f);
		result._33 = scaleZ;
		result._34 = static_cast<T>(0.0f);

		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	
	inline Matrix Translate(T offsetX, T offsetY, T offsetZ) const
	{
		Matrix <T> result;

		result._11 = static_cast<T>(1.0f);
		result._12 = static_cast<T>(0.0f);
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = static_cast<T>(0.0f);
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);

		resu.t._31 = static_cast<T>(0.0f);
		result._32 = static_cast<T>(0.0f);
		result._33 = static_cast<T>(0.0f);
		result._34 = static_cast<T>(0.0f);

		result._41 = offsetX;
		result._42 = offsetY;
		result._43 = offsetZ;
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	
	inline Matrix RotationX(T angle)
	{
		Matrix <T> result;
		T v_sin = static_cast<T>(sin(angle));
		T v_cos = static_cast<T>(cos(angle));

		result._11 = static_cast<T>(1.0f);
		result._12 = static_cast<T>(0.0f);
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = v_cos;
		result._23 = v_sin;
		result._24 = static_cast<T>(0.0f);

		result._31 = static_cast<T>(0.0f);
		result._32 = -v_sin;
		result._33 = v_cos;
		result._34 = static_cast<T>(0.0f);

		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	inline Matrix RotationY(T angle)
	{
		Matrix <T> result;
		T v_sin = static_cast<T>(sin(angle));
		T v_cos = static_cast<T>(cos(angle));

		result._11 = v_cos;
		result._12 = static_cast<T>(0.0f);
		result._13 = -v_sin;
		result._14 = static_cast<T>(0.0f);
		
		result._21 = static_cast<T>(0.0f);
		result._22 = static_cast<T>(1.0f);
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);

		result._31 = v_sin;
		result._32 = static_cast<T>(0.0f);
		result._33 = v_cos;
		result._34 = static_cast<T>(0.0f);

		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	inline Matrix RotationZ(T angle)
	{
		Matrix <T> result;
		T v_sin = static_cast<T>(sin(angle));
		T v_cos = static_cast<T>(cos(angle));

		result._11 = v_cos;
		result._12 = v_sin;
		result._13 = static_cast<T>(0.0f);
		result._14 = static_cast<T>(0.0f);

		result._21 = static_cast<T>(0.0f);
		result._22 = static_cast<T>(1.0f);
		result._23 = static_cast<T>(0.0f);
		result._24 = static_cast<T>(0.0f);

		result._31 = v_sin;
		result._32 = v_cos;
		result._33 = static_cast<T>(0.0f);
		result._34 = static_cast<T>(0.0f);
		
		result._41 = static_cast<T>(0.0f);
		result._42 = static_cast<T>(0.0f);
		result._43 = static_cast<T>(0.0f);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	
	// 获得 视口矩阵
	Matrix	LookAtLH(const Vector4 <T>& eye, const Vector4 <T>& at, const Vector4 <T>& up) const
	{
		Vector4 <T> axisZ = (at - eye).Normalize();
		Vector4 <T> axisX = up.Cross(axisZ).Normalize();
		Vector4 <T> axisY = axisZ.Cross(axisX);

		Matrix <T> result;
		result._11 = axisX.x_;
		result._12 = axisY.x_;
		result._13 = axisZ.x_;
		result._14 = static_cast<T>(0.0f);

		result._21 = axisX.y_;
		result._22 = axisY.y_;
		result._23 = axisZ.y_;
		result._24 = static_cast<T>(0.0f);

		result._31 = axisX.z_;
		result._32 = axisY.z_;
		result._33 = axisZ.z_;
		result._34 = static_cast<T>(0.0f);

		result._41 = -axisX.Dot(eye);
		result._42 = -axisY.Dot(eye);
		result._43 = -axisZ.Dot(eye);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	/*
	Matrix LookAtLH(Vector4 <T>& eye, Vector4 <T>& at, Vector4 <T>& up) const
	{
		Vector4 <T> axisZ = (at - eye).Normalize();
		Vector4 <T> axisX = axisZ.Cross(up).Normalize();
		Vector4 <T> axisY = axisZ.Cross(-axisX).Normalize();

		Matrix <T> result;
		result._11 = axisX.x_;
		result._12 = axisX.y_;
		result._13 = axisX.z_;
		result._14 = static_cast<T>(0.0f);

		result._21 = axisY.x_;
		result._22 = axisY.y_;
		result._23 = axisY.z_;
		result._24 = static_cast<T>(0.0f);

		result._31 = axisZ.x_;
		result._32 = axisZ.y_;
		result._33 = axisZ.z_;
		result._34 = static_cast<T>(0.0f);

		result._41 = -axisX.Dot(eye);
		result._42 = -axisY.Dot(eye);
		result._43 = -axisZ.Dot(eye);
		result._44 = static_cast<T>(1.0f);

		return result;
	}
	*/

	Matrix PerspectiveFovLH(T fovY, T aspect, T nZ, T fZ) const
	{
		Matrix <T> result;
		T h = static_cast<T>(1.0f) / tan(fovY * static_cast<T>(0.5f));

		result = result.SetZero();
		result._11 = h / aspect;
		result._22 = h;
		result._33 = fZ / (fZ - nZ);
		result._34 = static_cast<T>(1.0f);
		result._43 = (nZ * fZ) / (nZ - fZ);
		
		return result;
	}

	Matrix ScreenTransform(size_t clientWidth, size_t clientHeight)
	{
		Matrix <T> result;
		result = result.SetZero();

		result._11 = static_cast<T>(clientWidth / 2);
		result._22 = static_cast<T>(clientHeight / 2);
		result._33 = static_cast<T>(1.0f);
		result._41 = static_cast<T>(clientWidth / 2);
		result._42 = static_cast<T>(clientHeight / 2);
		result._44 = static_cast<T>(1.0f);

		return result;
	}

	/*
	// for Vector2
	// Transform (x, y, 0, 1) by matrix, project result back w_=1
	Vector4 <T> Transform(const Vector2 <T>& vector2) const
	{

	}

	// Transform (x, y, 0, 1) by matrix.
	Vector2 <T> TransformCoord(const Vector2 <T>& vector2) const
	{

	}

	// Transform (x, y, 0, 0) by matrix.
	Vector2 <T> TransformNormal(const Vector2 <T>& vector2) const
	{

	}

	// for Vector3.
	// Transform (x, y, z, 1) by matrix, project result back _w = 1.
	Vector4 <T> Transform(const Vector3 <T>& vector3) const
	{

	}

	// Transform (x, y, z, 1) by matrix.
	Vector3 <T> TransformCoord(const Vector3 <T>& vector2) const
	{

	}

	// Transform (x, y, z, 0) by matrix.
	Vector3 <T> TransformNormal(const Vector3 <T>& vector3) const
	{

	}


	// for Vector4
	// Transform (x, y, z, 1) matrix, project result back_w = 1.
	Vector4 <T> Transform(const Vector3 <T>& vector4) const
	{

	}

	Vector4 <T> TransformCoord(const Vector4 <T>& vector4) const
	{

	}

	Vector4 <T> TransformNormal(const Vector4 <T>& vector4) const
	{

	}


	*/


public:
	union
	{

		T m[4][4];
		T n[16];

		struct
		{
			T _11; T _12; T _13; T _14; 
			T _21; T _22; T _23; T _24;
			T _31; T _32; T _33; T _34;
			T _41; T _42; T _43; T _44;
		};
	};
};


