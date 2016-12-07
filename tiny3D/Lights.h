#pragma once

#include "Math/Math.h"
#include <cstdlib>
#include <algorithm>


namespace Lights
{

	template <typename T>
	struct DirectionalLight
	{
		DirectionalLight() { memset(this, 0, sizeof(this)); }

		Vector4 <T> ambient_;
		Vector4 <T> diffuse_;
		Vector4 <T> specular_;
		Vector4 <T> direction_;
	};

	template <typename T>
	struct PointLight
	{
		PointLight() { memset(this, 0, sizeof(this)); }
		
		Vector4 <T> ambient_;
		Vector4 <T> diffuse_;
		Vector4 <T> specular_;
		Vector4 <T> position_;
		Vector4 <T> att_;
		T range_;
	};

	template <typename T>
	struct SpotLight
	{
		SpotLight() { memset(this, 0, sizeof(this)); }

		Vector4 <T> ambient_;
		Vector4 <T> diffuse_;
		Vector4 <T> specular_;
		Vector4 <T> position_;
		Vector4 <T> direction_;
		Vector4 <T> att_;
		T range_;
		T spot_;		
	};


	template <typename T>
	struct Material
	{
		Material() { memset(this, 0, sizeof(0)); }

		Vector4 <T> ambient_;
		Vector4 <T> diffuse_;
		Vector4 <T> specular_;	// w 表示 光照强度
		Vector4 <T> reflect_;
	};


	template <typename T>
	inline void ComputeDirectionalLight(
		const Material <T>& mat,
		const DirectionalLight <T>& dL,
		const Vector4 <T>& normal,
		const Vector4 <T>& toEye,
		Vector4 <T>& ambient,
		Vector4 <T>& diffuse,
		Vector4 <T>& spec)
	{

		ambient = Vector4 <T>(static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f));

		diffuse = Vector4 <T>(static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f));

		spec = Vector4 <T>(static_cast<T>(0.0f),
						   static_cast<T>(0.0f),
						   static_cast<T>(0.0f),
						   static_cast<T>(0.0f));

		// 计算 光线方向
		Vector4 <T> lightVec = -dL.direction_;
		// 计算 环境光
		ambient = mat.ambient_ * dL.ambient_;

		// 计算漫反射系数
		// 光线、法线方向单位化
		lightVec = lightVec.Normalize();
		T diffuseFactor = lightVec.Dot(normal);

		// 顶点背向光源不再计算
		if (diffuseFactor > static_cast<T>(0.0f)) {
			
			// 入射光线关于法线的反射向量
			Vector4 <T> v = Reflect(-lightVec, normal);

			T spectFactor = pow(TpMax(v.Dot(toEye), static_cast<T>(0.0f)), mat.specular_.w_);
			
			// 计算漫反射光
			diffuse = mat.diffuse_ * dL.diffuse_ * diffuseFactor;

			// 计算高光
			spec = mat.specular_ * dL.specular_ * spectFactor;
		}
	}
	

	template <typename T>
	inline void ComputePointLight(
		const Material <T>& mat,
		const PointLight <T>& pL,
		const Vector4 <T>& pos,
		const Vector4 <T>& normal,
		const Vector4 <T>& toEye,
		Vector4 <T>& ambient,
		Vector4 <T>& diffuse,
		Vector4 <T>& spec)
	{
		ambient = Vector4 <T>(static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f));

		diffuse = Vector4 <T>(static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f),
							  static_cast<T>(0.0f));

		spec = Vector4 <T>(static_cast<T>(0.0f),
						   static_cast<T>(0.0f),
						   static_cast<T>(0.0f),
						   static_cast<T>(0.0f));

		// 计算 光线方向
		Vector4 <T> lightVec = pL.position_ - pos;

		// 计算顶点到光源距离
		T d = lightVec.Length();

		// 超过范围不再计算
		if (d > pL.range_) {
			return;
		}

		// 单位化光照方向
		lightVec = lightVec * (static_cast<T>(1.0f) / d);

		// 计算环境光
		ambient = mat.ambient_ * pL.ambient_;

		// 漫反射系数
		T diffuseFactor = lightVec.Dot(normal);

		// 顶点背向光源不再计算
		if (diffuseFactor > static_cast<T>(0.0f)) {

			// 入射光线关于法线的反射向量
			Vector4 <T> v = Reflect(-lightVec, normal);

			T spectFactor = pow(TpMax(v.Dot(toEye), static_cast<T>(0.0f)), mat.specular_.w_);

			// 计算漫反射光
			diffuse = mat.diffuse_ * pL.diffuse_ * diffuseFactor;

			// 计算高光
			spec = mat.specular_ * pL.specular_ * spectFactor;
		}

		T att = static_cast<T>(1.0f) / pL.att_.Dot(Vector4 <T>(static_cast<T>(1.0f), d, d * d));
		diffuse = diffuse * att;
		spec = diffuse * att;
	}


	template <typename T> 
	inline void ComputeSpotLight(
		const Material <T>& mat,
		const SpotLight <T>& sl,
		const Vector4 <T>& pos,
		const Vector4 <T>& normal,
		const Vector4 <T>& toEye,
		Vector4 <T>& ambient,
		Vector4 <T>& diffuse,
		Vector4 <T>& spec)
	{

		ambient = Vector4 <T>(static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f));

		diffuse = Vector4 <T>(static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f));

		spec = Vector4 <T>(static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			static_cast<T>(0.0f));

		// 光照方向：顶点到光源
		Vector4 <T> lightVec = sl.position_ - pos;

		// 顶点到光源距离
		T d = lightVec.Length();

		// 距离大于光照方向，不再计算
		if (d > sl.range_) {
			return;
		}

		// 单位化光照方向
		lightVec = lightVec * (1.0f / d);


		// 计算环境光
		ambient = mat.ambient_ * sl.ambient_;
		// 计算漫反射系数
		T diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > static_cast<T>(0.0f)) {
			Vector4 <T> v = Reflect(-lightVec, normal);
			T specFactor = pow(TpMax(v.Dot(toEye), static_cast<T>(0.0f)), mat.specular_.w_);

			// 漫反射光
			diffuse = mat.diffuse_ * sl.diffuse_ * diffuseFactor;
			// 高光
			spec = mat.specular_ * sl.specular_ * specFactor;
		}

		// 聚光衰弱系数
		T spotFactor = pow(TpMax(-lightVec.Dot(sl.direction_), static_cast<T>(0.0f)), sl.spot_);
		// 衰弱系数
		T att = spotFactor / sl.att_.Dot(Vector4 <T>(static_cast<T>(1.0f), d, d * d));
		ambient = ambient * spotFactor;
		diffuse = diffuse * att;
		spec = spec * att;
	}

	
	typedef struct DirectionalLight <float> FDirectionalLight;
	typedef struct DirectionalLight <double> DDirectionalLight;

	typedef struct PointLight <float> FPointLight;
	typedef struct PointLight <double> DPointLight;

	typedef struct SpotLight <float> FSpotLight;
	typedef struct SpotLight <double> DSpotLight;

	typedef struct Material <float> FMaterial;
	typedef struct Material <double> DMaterial;
}