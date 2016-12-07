#pragma once

#include "Vertex.h"
#include "Math/Math.h"
#include "Lights.h"


template <typename T>
class ShaderBase
{
public:
	ShaderBase() = default;
	virtual ~ShaderBase() {}

public:
	virtual VertexOut <T> VS(const VertexIn <T>& vin) = 0;
	virtual Vector4 <T> PS(VertexOut <T>& pin) = 0;

};