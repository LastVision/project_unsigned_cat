#pragma once
#include <hge.h>
#include <Vector.h>
class Sprite
{
public:
	Sprite();
	Sprite(const HTEXTURE& aTexture, const float aXPosition, const float aYPosition, const float aWidth, const float aHeight, HGE* aHgeHandler);
	~Sprite();

	inline void SetPosition(const float aXPosition, const float aYPosition);
	inline void SetPosition(const int aXPosition, const int aYPosition);

	inline void SetColor(const Vector4<float>& aColor);
	
	inline void SetBlend(const int aBlendMode);

	inline void SetZBuffer(const float aZBuffer);

	inline const hgeQuad& GetSprite() const;

private:
	void UpdateSprite();
	void UpdatePosition();
	void UpdateColor();
	void UpdateTextureRect();
private:
	hgeQuad mySprite;
	Vector2<float> myTextureSize;
	Vector2<float> mySpriteSize;
	Vector2<float> myTexturePosition;
	Vector2<float> myScreenPosition;
	Vector4<float> myColor;
	float myZBuffer;

};

const hgeQuad& Sprite::GetSprite() const
{
	return mySprite;
}

void Sprite::SetPosition(const float aXPosition, const float aYPosition)
{
	myScreenPosition.x = aXPosition;
	myScreenPosition.y = aYPosition;
	UpdatePosition();
}

void Sprite::SetPosition(const int aXPosition, const int aYPosition)
{
	myScreenPosition.x = static_cast<float>(aXPosition);
	myScreenPosition.y = static_cast<float>(aYPosition);
	UpdatePosition();
}

void Sprite::SetColor(const Vector4<float>& aColor)
{
	myColor = aColor;
	UpdateColor();
}

void Sprite::SetBlend(const int aBlendMode)
{
	mySprite.blend = aBlendMode;
}

void Sprite::SetZBuffer(const float aZBuffer)
{
	myZBuffer = aZBuffer;
	UpdateColor();
}