#pragma once

#include <cmath>

const double ACCURACY_ERROR = 1e-6;
const double PI = acos(-1.0);

template <typename T>
inline T TpMax(T v1, T v2)
{
	if (v1 > v2) {
		return v1;
	}
	return v2;
}


template <typename T>
inline T TpMin(T v1, T v2)
{
	if (v1 > v2) {
		return v2;
	}
	return v1;
}

// 使用 直接误差 或 相对误差 进行判断 精度问题
template <typename T>
bool TpIsEqual(T a, T b)
{
	T diff = fabs(a - b);
	if (diff <= static_cast<T>(ACCURACY_ERROR)) {
		return true;
	}
	else {
		if (a >= static_cast<T>(1.0f)) {
			return (diff / fabs(a) <= static_cast<T>(ACCURACY_ERROR));
		}
	}

	return false;
}