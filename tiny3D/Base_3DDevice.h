#pragma once

#include <cstdlib>
#include "Math/Math.h"

template <typename T>
class Base_3DDevice
{
public:
	Base_3DDevice(size_t width, size_t height)
	{
		width_ = width;
		height_ = height;
		zBuffer_ = new T*[width];
		zBuffer_[0] = new T[width * height];

		for (size_t i = 1; i < width_; ++i) {
			zBuffer_[i] = zBuffer_[0] + i * height_;
		}
	}

	~Base_3DDevice()
	{
		if (pFrameBuffer_) {
			delete[] pFrameBuffer_;
		}

		if (zBuffer_) {
			delete[] zBuffer_[0];
			delete[] zBuffer_;
		}
	}

public:
	void DrawPixel(size_t x, size_t y, Vector3 <T> &color)
	{
		pFrameBuffer_[width_ * y + x] = ColorToUInt(color);
	}

	void DrawPixel(size_t x, size_t y, Vector4 <T> &color)
	{
		pFrameBuffer_[width_ * y + x] = ColorToUInt(color);
	}

	T GetZ(size_t x, size_t y) const
	{
		if (x < width_ && y < height_) {
			return zBuffer_[x][y];
		}
		else {
			return static_cast<T>(1.0f);
		}
	}
	void SetZ(size_t x, size_t y, T z)
	{
		if (x < width_ && y < height_) {
			zBuffer_[x][y] = z;
		}
	}

	UINT *&GetFrameBuffer()
	{
		return pFrameBuffer_;
	}

	inline size_t GetClientWidth() const
	{
		return width_;
	}

	inline size_t GetClientHeight() const
	{
		return height_;
	}

	void ClearBuffer(const Vector3 <T> &color)
	{
		memset(zBuffer_[0], 0, width_ * height_ * sizeof(T));
		unsigned int valueColor = ColorToUInt(color);

		for (size_t i = 0; i < width_; ++i) {
			for (size_t j = 0; j < height_; ++j) {
				pFrameBuffer_[height_ * i + j] = valueColor;
			}
		}
	}

	void ClearBuffer(const Vector4 <T> &color)
	{
		memset(zBuffer_[0], 0, width_ * height_ * sizeof(T));
		unsigned int valueColor = ColorToUInt(color);

		for (size_t i = 0; i < width_; ++i) {
			for (size_t j = 0; j < height_; ++j) {
				pFrameBuffer_[height_ * i + j] = valueColor;
			}
		}
	}

private:
	size_t width_;
	size_t height_;
	UINT *pFrameBuffer_;
	T **zBuffer_;
};


typedef Base_3DDevice <float> FBase_3DDevice;
typedef Base_3DDevice <double> DBase_3DDevice;
