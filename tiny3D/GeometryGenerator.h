#pragma once

#include "Math/Math.h"
#include "Vertex.h"
#include <vector>

template <typename T>
struct _MeshData
{
	std::vector<VertexIn <T>> vertices_;
	std::vector<UINT> indices_;
};

template <typename T>
class GeometryGenerator
{
private:
	GeometryGenerator() {}

public:
	// 单例模式
	static GeometryGenerator* GetInstance()
	{
		static GeometryGenerator <T>instance;
		return &instance;
	}

	// 基本网络结构：顶点集合 + 索引集合
	
	_MeshData <T> MeshData;


	// 指定 宽(x)、 高(y)、深(z)
	// 创建一个立方体
	void CreateBox(T width, T height, T depth, _MeshData <T>& mesh)
	{
		mesh.vertices_.clear();
		mesh.indices_.clear();

		//一共24个顶点(每面4个)
		mesh.vertices_.resize(24);
		//一共36个索引(每面6个)
		mesh.indices_.resize(36);
		
		T halfW = width * static_cast<T>(0.5f);
		T halfH = height * static_cast<T>(0.5f);
		T halfD = depth * static_cast<T>(0.5f);

		//眼睛面向z轴正方向
		//构建顶点
		//前面

		T v_0 = static_cast<T>(0.0f);
		T v_1 = static_cast<T>(1.0f);

		mesh.vertices_[0].pos_ = Vector4 <T>(-halfW, -halfH, -halfD, v_1);
		mesh.vertices_[0].normal_ = Vector4 <T>(v_0, v_0, -v_1);
		mesh.vertices_[0].color_ = Vector4 <T>(v_1, v_0, v_0, v_1);
		mesh.vertices_[0].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[1].pos_ = Vector4 <T>(-halfW, halfH, -halfD, v_1);
		mesh.vertices_[1].normal_ = Vector4 <T>(v_0, v_0, -v_1);
		mesh.vertices_[1].color_ = Vector4 <T>(v_0, v_0, v_0, v_1);
		mesh.vertices_[1].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[2].pos_ = Vector4 <T>(halfW, halfH, -halfD, v_1);
		mesh.vertices_[2].normal_ = Vector4 <T>(v_0, v_0, -v_1);
		mesh.vertices_[2].color_ = Vector4 <T>(v_1, v_0, v_0, v_1);
		mesh.vertices_[2].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[3].pos_ = Vector4 <T>(halfW, -halfH, -halfD, v_1);
		mesh.vertices_[3].normal_ = Vector4 <T>(v_0, v_0, -v_1);
		mesh.vertices_[3].color_ = Vector4 <T>(v_0, v_1, v_0, v_1);
		mesh.vertices_[3].tex_ = Vector2 <T>(v_1, v_1);
		//左侧面
		mesh.vertices_[4].pos_ = Vector4 <T>(-halfW, -halfH, halfD, v_1);
		mesh.vertices_[4].normal_ = Vector4 <T>(-v_1, v_0, v_0);
		mesh.vertices_[4].color_ = Vector4 <T>(v_0, v_0, v_1, v_1);
		mesh.vertices_[4].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[5].pos_ = Vector4 <T>(-halfW, halfH, halfD, v_1);
		mesh.vertices_[5].normal_ = Vector4 <T>(-v_1, v_0, v_0);
		mesh.vertices_[5].color_ = Vector4 <T>(v_1, v_1, v_0, v_1);
		mesh.vertices_[5].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[6].pos_ = Vector4 <T>(-halfW, halfH, -halfD, v_1);
		mesh.vertices_[6].normal_ = Vector4 <T>(-v_1, v_0, v_0);
		mesh.vertices_[6].color_ = Vector4 <T>(v_0, v_0, v_0, v_1);
		mesh.vertices_[6].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[7].pos_ = Vector4 <T>(-halfW, -halfH, -halfD, v_1);
		mesh.vertices_[7].normal_ = Vector4 <T>(-v_1, v_0, v_0);
		mesh.vertices_[7].color_ = Vector4 <T>(v_1, v_1, v_1, v_1);
		mesh.vertices_[7].tex_ = Vector2 <T>(v_1, v_1);
		//背面
		mesh.vertices_[8].pos_ = Vector4 <T>(halfW, -halfH, halfD, v_1);
		mesh.vertices_[8].normal_ = Vector4 <T>(v_0, v_0, v_1);
		mesh.vertices_[8].color_ = Vector4 <T>(v_1, v_0, v_1, v_1);
		mesh.vertices_[8].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[9].pos_ = Vector4 <T>(halfW, halfH, halfD, v_1);
		mesh.vertices_[9].normal_ = Vector4 <T>(v_0, v_0, v_1);
		mesh.vertices_[9].color_ = Vector4 <T>(v_0, v_1, v_1, v_1);
		mesh.vertices_[9].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[10].pos_ = Vector4 <T>(-halfW, halfH, halfD, v_1);
		mesh.vertices_[10].normal_ = Vector4 <T>(v_0, v_0, v_1);
		mesh.vertices_[10].color_ = Vector4 <T>(v_1, v_1, v_0, v_1);
		mesh.vertices_[10].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[11].pos_ = Vector4 <T>(-halfW, -halfH, halfD, v_1);
		mesh.vertices_[11].normal_ = Vector4 <T>(v_0, v_0, v_1);
		mesh.vertices_[11].color_ = Vector4 <T>(v_0, v_0, v_1, v_1);
		mesh.vertices_[11].tex_ = Vector2 <T>(v_1, v_1);
		//右侧面
		mesh.vertices_[12].pos_ = Vector4 <T>(halfW, -halfH, -halfD, v_1);
		mesh.vertices_[12].normal_ = Vector4 <T>(v_1, v_0, v_0);
		mesh.vertices_[12].color_ = Vector4 <T>(v_0, v_1, v_0, v_1);
		mesh.vertices_[12].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[13].pos_ = Vector4 <T>(halfW, halfH, -halfD, v_1);
		mesh.vertices_[13].normal_ = Vector4 <T>(v_1, v_0, v_0);
		mesh.vertices_[13].color_ = Vector4 <T>(v_1, v_0, v_0, v_1);
		mesh.vertices_[13].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[14].pos_ = Vector4 <T>(halfW, halfH, halfD, v_1);
		mesh.vertices_[14].normal_ = Vector4 <T>(v_1, v_0, v_0);
		mesh.vertices_[14].color_ = Vector4 <T>(v_0, v_1, v_1, v_1);
		mesh.vertices_[14].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[15].pos_ = Vector4 <T>(halfW, -halfH, halfD, v_1);
		mesh.vertices_[15].normal_ = Vector4 <T>(v_1, v_0, v_0);
		mesh.vertices_[15].color_ = Vector4 <T>(v_1, v_0, v_1, v_1);
		mesh.vertices_[15].tex_ = Vector2 <T>(v_1, v_1);
		//上面
		mesh.vertices_[16].pos_ = Vector4 <T>(-halfW, halfH, -halfD, v_1);
		mesh.vertices_[16].normal_ = Vector4 <T>(v_0, v_1, v_0);
		mesh.vertices_[16].color_ = Vector4 <T>(v_0, v_0, v_0, v_1);
		mesh.vertices_[16].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[17].pos_ = Vector4 <T>(-halfW, halfH, halfD, v_1);
		mesh.vertices_[17].normal_ = Vector4 <T>(v_0, v_1, v_0);
		mesh.vertices_[17].color_ = Vector4 <T>(v_1, v_1, v_0, v_1);
		mesh.vertices_[17].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[18].pos_ = Vector4 <T>(halfW, halfH, halfD, v_1);
		mesh.vertices_[18].normal_ = Vector4 <T>(v_0, v_1, v_0);
		mesh.vertices_[18].color_ = Vector4 <T>(v_0, v_1, v_1, v_1);
		mesh.vertices_[18].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[19].pos_ = Vector4 <T>(halfW, halfH, -halfD, v_1);
		mesh.vertices_[19].normal_ = Vector4 <T>(v_0, v_1, v_0);
		mesh.vertices_[19].color_ = Vector4 <T>(v_1, v_0, v_0, v_1);
		mesh.vertices_[19].tex_ = Vector2 <T>(v_1, v_1);
		//底面
		mesh.vertices_[20].pos_ = Vector4 <T>(-halfW, -halfH, halfD, v_1);
		mesh.vertices_[20].normal_ = Vector4 <T>(v_0, -v_1, v_0);
		mesh.vertices_[20].color_ = Vector4 <T>(v_0, v_0, v_1, v_1);
		mesh.vertices_[20].tex_ = Vector2 <T>(v_0, v_1);
		mesh.vertices_[21].pos_ = Vector4 <T>(-halfW, -halfH, -halfD, v_1);
		mesh.vertices_[21].normal_ = Vector4 <T>(v_0, -v_1, v_0);
		mesh.vertices_[21].color_ = Vector4 <T>(v_1, v_1, v_1, v_1);
		mesh.vertices_[21].tex_ = Vector2 <T>(v_0, v_0);
		mesh.vertices_[22].pos_ = Vector4 <T>(halfW, -halfH, -halfD, v_1);
		mesh.vertices_[22].normal_ = Vector4 <T>(v_0, -v_1, v_0);
		mesh.vertices_[22].color_ = Vector4 <T>(v_0, v_1, v_0, v_1);
		mesh.vertices_[22].tex_ = Vector2 <T>(v_1, v_0);
		mesh.vertices_[23].pos_ = Vector4 <T>(halfW, -halfH, halfD, v_1);
		mesh.vertices_[23].normal_ = Vector4 <T>(v_0, -v_1, v_0);
		mesh.vertices_[23].color_ = Vector4 <T>(v_1, v_0, v_1, v_1);
		mesh.vertices_[23].tex_ = Vector2 <T>(v_1, v_1);

		//构建索引
		mesh.indices_[0] = 0;
		mesh.indices_[1] = 1;
		mesh.indices_[2] = 2;
		mesh.indices_[3] = 0;
		mesh.indices_[4] = 2;
		mesh.indices_[5] = 3;

		mesh.indices_[6] = 4;
		mesh.indices_[7] = 5;
		mesh.indices_[8] = 6;
		mesh.indices_[9] = 4;
		mesh.indices_[10] = 6;
		mesh.indices_[11] = 7;

		mesh.indices_[12] = 8;
		mesh.indices_[13] = 9;
		mesh.indices_[14] = 10;
		mesh.indices_[15] = 8;
		mesh.indices_[16] = 10;
		mesh.indices_[17] = 11;

		mesh.indices_[18] = 12;
		mesh.indices_[19] = 13;
		mesh.indices_[20] = 14;
		mesh.indices_[21] = 12;
		mesh.indices_[22] = 14;
		mesh.indices_[23] = 15;

		mesh.indices_[24] = 16;
		mesh.indices_[25] = 17;
		mesh.indices_[26] = 18;
		mesh.indices_[27] = 16;
		mesh.indices_[28] = 18;
		mesh.indices_[29] = 19;

		mesh.indices_[30] = 20;
		mesh.indices_[31] = 21;
		mesh.indices_[32] = 22;
		mesh.indices_[33] = 20;
		mesh.indices_[34] = 22;
		mesh.indices_[35] = 23;
	}

	// 创建一个三角形
	void CreateTriangle(T width, T height, T depth, _MeshData <T>& mesh)
	{

	}
};