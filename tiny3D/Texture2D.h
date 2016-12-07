#pragma once

#include <cstdlib>
#include <assert.h>
#include "Math/Vector.h"


template <typename T>
class Texture2D
{

public:

	Texture2D()
	{
		width_ = 0;
		height_ = 0;
		pixelBuffer_ = nullptr;
	}

	
	Texture2D(const size_t width, const size_t height) :
		width_(width), height_(height)
	{
		pixelBuffer_ = new Vector4 <T>* [width_];
		pixelBuffer_[0] = new Vector4 <T>[width_ * height_];
		for (size_t i = 1; i < width_; ++i) {
			pixelBuffer_[i] = pixelBuffer_[0] + i * height_;
		}
	}

	Texture2D(const Texture2D <T>& texture2D)
	{
		width_ = texture2D.width_;
		height_ = texture2D.height_;

		pixelBuffer_ = new Vector4 <T>*[width_];
		pixelBuffer_[0] = new Vector4 <T>[width_ * height_];
		for (size_t i = 1; i < width_; ++i) {
			pixelBuffer_[i] = pixelBuffer_[0] + i * height_;
		}

		for (size_t i = 0; i < width_; ++i) {
			for (size_t j = 0; j < height_; ++j) {
				pixelBuffer_[i][j] = texture2D.pixelBuffer_[i][j];
			}
		}
	}


	~Texture2D()
	{
		if (pixelBuffer_ != nullptr) {
			delete[] pixelBuffer_[0];
			delete[] pixelBuffer_;

			width_ = 0;
			height_ = 0;
			pixelBuffer_ = nullptr;
		}
	}

	Texture2D& operator = (const Texture2D <T>& texture2D)
	{
		if (this == &texture2D) {
			return *this;
		}

		width_ = texture2D.width_;
		height_ = texture2D.height_;

		pixelBuffer_ = new Vector4 <T>*[width_];
		pixelBuffer_[0] = new Vector4 <T>[width_ * height_];
		for (size_t i = 1; i < width_; ++i) {
			pixelBuffer_[i] = pixelBuffer_[0] + i * height_;
		}

		for (size_t i = 0; i < width_; ++i) {
			for (size_t j = 0; j < height_; ++j) {
				pixelBuffer_[i][j] = texture2D.pixelBuffer_[i][j];
			}
		}

		return *this;
	}

	Vector4 <T> Sample(const Vector2 <T>& texPos)
	{

		if (texPos.x_ >= static_cast<T>(0.0f) &&
			texPos.x_ <= static_cast<T>(1.0f) &&
			texPos.y_ >= static_cast<T>(0.0f) &&
			texPos.y_ <= static_cast<T>(1.0f)) {

			size_t x = static_cast<size_t>(texPos.x_ * (width_ - 1));
			size_t y = static_cast<size_t>(texPos.y_ * (height_ - 1));

			return pixelBuffer_[x][y];
		}

		else {
		
			T x, y;

			x = static_cast<T>(0.0f);
			y = static_cast<T>(0.0f);

			if (typeid(T) == typeid(float)) {
				if (texPos.x_ >= 1.0f) {
					x = texPos.x_ - static_cast<T>(static_cast<int>(texPos.x_));
				}
				else {
					x = texPos.x_ + static_cast<T>(1 - static_cast<int>(texPos.x_));
				}

				if (texPos.y_ >= 1.0f) {
					y = texPos.y_ - static_cast<T>(static_cast<int>(texPos.x_));
				}
				else {
					y = texPos.y_ + static_cast<T>(1 - static_cast<int>(texPos.y_));
				}
			}

			else if(typeid(T) == typeid(double)) {
				if (texPos.x_ >= 1.0) {
					x = texPos.x_ - static_cast<T>(static_cast<long long>(texPos.x_));
				}
				else {
					x = texPos.x_ + static_cast<T>(1 - static_cast<long long>(texPos.x_));
				}

				if (texPos.y_ >= 1.0) {
					y = texPos.y_ - static_cast<T>(static_cast<long long>(texPos.x_));
				}
				else {
					y = texPos.y_ + static_cast<T>(1 - static_cast<long long>(texPos.y_));
				}

				

			}

			else {
				assert(false && "you can only template by double or float!");
			}


			
			size_t row = static_cast<size_t>(x * (width_ - 1));
			size_t col = static_cast<size_t>(y * (height_ - 1));

			if (row >= width_) {
				row = 0;
				//assert(0);
			}
			if (col >= height_) {
				col = 0;
				//assert(0);
			}

			return pixelBuffer_[row][col];
			
			//return pixelBuffer_[0][0];
		}
	}

	
public:
	size_t width_;
	size_t height_;
	Vector4 <T> **pixelBuffer_;
};


typedef Texture2D <float> FTexture2D;
typedef Texture2D <double> DTexture2D;



template <typename T>
Texture2D <T> Make_Tex_Rainbow(T tip)
{
	const size_t width = 255;
	const size_t height = 255;
	Texture2D <T> tex(width, height);
	Vector4 <T> pixel1, pixel2, pixel3;

	pixel1.x_ = static_cast<T>(1.0f);
	pixel1.y_ = static_cast<T>(1.0f);
	pixel1.z_ = static_cast<T>(1.0f);
	pixel1.w_ = static_cast<T>(1.0f);

	pixel2.x_ = static_cast<T>(0.7f);
	pixel2.y_ = static_cast<T>(0.5f);
	pixel2.z_ = static_cast<T>(0.9f);
	pixel2.w_ = static_cast<T>(0.0f);

	
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			pixel3.x_ = static_cast<T>(i + 1) * pixel1.x_ + static_cast<T>(j + 1) * pixel2.x_;
			pixel3.y_ = static_cast<T>(i + 1) * pixel1.y_ + static_cast<T>(j + 1) * pixel2.y_;
			pixel3.z_ = static_cast<T>(i + 1) * pixel1.z_ + static_cast<T>(j + 1) * pixel2.z_;
			pixel3.w_ = static_cast<T>(0.0f);

			tex.pixelBuffer_[i][j] = pixel1;
		}
	}

	return tex;
}