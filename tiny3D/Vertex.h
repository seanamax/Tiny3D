#pragma once


template <typename T>
class VertexIn
{
public:
	Vector4 <T> pos_;
	Vector4 <T> color_;
	Vector2 <T> tex_;
	Vector4 <T> normal_;

	VertexIn() = default;
	VertexIn(const Vector4 <T>& pos, const Vector4 <T>& color, const Vector2 <T>& tex, const Vector4 <T>& normal) :
		pos_(pos), color_(color), tex_(tex), normal_(normal) {}

	VertexIn(const VertexIn& vtn) : pos_(vtn.pos_), color_(vtn.color_), tex_(vtn.tex_), normal_(vtn.normal_) {}

};

template <typename T>
class VertexOut
{
public:
	VertexOut() = default;
	VertexOut(const Vector4 <T>& posT, const Vector4 <T>& posH, const Vector2 <T>& tex, const Vector4 <T>& normal,
		const Vector4 <T>& color, const T oneDivZ) : posTrans_(posT), posH_(posH), tex_(tex), normal_(normal),
		color_(color), oneDivZ_(oneDivZ) {}

	VertexOut & operator = (const VertexOut <T>& vOut)
	{
		if (this == &vOut) {
			return *this;
		}

		posTrans_ = vOut.posTrans_;
		posH_ = vOut.posH_;
		tex_ = vOut.tex_;
		normal_ = vOut.normal_;
		color_ = vOut.color_;

		return *this;
	}

	VertexOut Lerp(const VertexOut <T>& vOut, T lerpFactor) const
	{
		VertexOut <T> result;
		result.posH_ = posH_.Lerp(vOut.posH_, lerpFactor);
		result.posTrans_ = posTrans_.Lerp(vOut.posTrans_, lerpFactor);
		result.tex_ = tex_.Lerp(vOut.tex_, lerpFactor);
		result.normal_ = normal_.Lerp(vOut.normal_, lerpFactor);
		result.color_ = color_.Lerp(vOut.color_, lerpFactor);
		result.oneDivZ_ = TpLerp(oneDivZ_, vOut.oneDivZ_, lerpFactor);

		return result;
	}

public:
	Vector4 <T> posTrans_;
	Vector4 <T> posH_;
	Vector2 <T> tex_;

	Vector4 <T> normal_;
	Vector4 <T> color_;

	T oneDivZ_;
};


typedef VertexIn <float> FVertexIn;
typedef VertexIn <double> DVertexIn;

typedef VertexOut <float> FVertexOut;
typedef VertexOut <double> DVertexOut;
