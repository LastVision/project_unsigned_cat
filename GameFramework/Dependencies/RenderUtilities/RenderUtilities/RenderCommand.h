#pragma once
#include <Vector.h>
#include "Sprite\Sprite.h"

namespace RenderUtilities
{
	struct RenderCommand
	{
		inline RenderCommand();
		inline RenderCommand(const Sprite& aSprite, const Vector2<float>& aPosition);
		inline ~RenderCommand();
		Sprite mySprite;
		Vector2<float> myPosition;
	};
	RenderCommand::RenderCommand(const Sprite& aSprite, const Vector2<float>& aPosition)
	{
		mySprite = aSprite;
		myPosition = aPosition;
	}
	RenderCommand::RenderCommand()
	{

	}
	RenderCommand::~RenderCommand()
	{

	}
} namespace RU = RenderUtilities;