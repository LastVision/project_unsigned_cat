#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(const HTEXTURE& aTexture, const float aXPosition, const float aYPosition, const float aWidth, const float aHeight, HGE* aHgeHandler)
{
	mySprite.tex = aTexture;
	mySprite.blend = BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;
	mySpriteSize.x = aWidth;
	mySpriteSize.y = aHeight;

	myTexturePosition.x = aXPosition;
	myTexturePosition.y = aYPosition;

	myZBuffer = 0.5f;
	myColor = {255.f, 255.f, 255.f, 255.f};
	
	myTextureSize.x = static_cast<float>(aHgeHandler->Texture_GetWidth(aTexture, true));
	myTextureSize.y = static_cast<float>(aHgeHandler->Texture_GetHeight(aTexture, true));

	UpdateSprite();
	
	SetPosition(0, 0);
}

Sprite::~Sprite()
{
	
}

void Sprite::UpdateSprite()
{
	UpdateTextureRect();
	UpdatePosition();
	UpdateColor();
}

void Sprite::UpdateTextureRect()
{
	mySprite.v[0].tx = myTexturePosition.x / myTextureSize.x;
	mySprite.v[0].ty = myTexturePosition.y / myTextureSize.y;

	mySprite.v[1].tx = myTexturePosition.x + mySpriteSize.x / myTextureSize.x;
	mySprite.v[1].ty = myTexturePosition.y / myTextureSize.y;

	mySprite.v[2].tx = myTexturePosition.x + mySpriteSize.x / myTextureSize.x;
	mySprite.v[2].ty = myTexturePosition.y + mySpriteSize.y / myTextureSize.y;

	mySprite.v[3].tx = myTexturePosition.x / myTextureSize.x;
	mySprite.v[3].ty = myTexturePosition.y + mySpriteSize.y / myTextureSize.y;
}

void Sprite::UpdatePosition()
{
	mySprite.v[0].x = myScreenPosition.x;
	mySprite.v[0].y = myScreenPosition.y;

	mySprite.v[1].x = myScreenPosition.x + mySpriteSize.x;
	mySprite.v[1].y = myScreenPosition.y;

	mySprite.v[2].x = myScreenPosition.x + mySpriteSize.x;
	mySprite.v[2].y = myScreenPosition.y + mySpriteSize.y;

	mySprite.v[3].x = myScreenPosition.x;
	mySprite.v[3].y = myScreenPosition.y + mySpriteSize.y;
}

void Sprite::UpdateColor()
{
	for (int i = 0; i<4; i++)
	{
		mySprite.v[i].z = myZBuffer;
		mySprite.v[i].col = ARGB(myColor.a, myColor.r, myColor.g, myColor.b);
	}
}