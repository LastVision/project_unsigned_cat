#pragma once
#include <hge.h>
#include <GrowingArray.h>
#include <Syncronizer.h>
#include "../RenderCommand.h"
namespace RenderUtilities
{
	class Renderer
	{
	public:
		static void Create(HGE* aHgeHandler, Syncronizer* aSyncronizer);
		static void Destroy();
		static Renderer* GetInstance();

		void Render();
		void SetBackgroundColor(const DWORD &aColor);
		void RenderSprite(const Sprite& aSprite);

		void AddRenderCommand(const RU::RenderCommand& aRenderCommand);
	private:
		Renderer();
		virtual ~Renderer();

		bool Initialize(HGE* aHgeHandler, Syncronizer* aSyncronizer);
		void SwapBuffers();

		void StartRendering();
	private:
		HGE* myHgeHandler;
		Syncronizer* mySyncronizer;
		static Renderer* myInstance;

		CU::GrowingArray<CU::GrowingArray<RU::RenderCommand, int>, int> myRenderBuffers;
		int myActiveBuffer;

		DWORD myBackgroundColor;

		CU::GrowingArray<Sprite, int> mySpritesToRender;
	};
}namespace RU = RenderUtilities;