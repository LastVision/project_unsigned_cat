#include "Renderer.h"
#include <DL_Debug.h>

RU::Renderer* RU::Renderer::myInstance = nullptr;

RU::Renderer::Renderer()
{
	myHgeHandler = nullptr;
	myBackgroundColor = 0xFFFFFFFF;
	mySpritesToRender.Init(1024);
}

RU::Renderer::~Renderer()
{

}

void RU::Renderer::Create(HGE* aHgeHandler, Syncronizer* aSyncronizer)
{
	if (myInstance != nullptr)
	{
		DL_ASSERT("Render Instance are already created, you cannot have more than one renderer!");
	}
	myInstance = new Renderer();
	if (myInstance->Initialize(aHgeHandler, aSyncronizer) == false)
	{
		Destroy();
		DL_ASSERT("Failed to create Render instance. Missing HGEHandler and/or Syncronizer!");
	}
}

void RU::Renderer::Destroy()
{
	myInstance->mySpritesToRender.RemoveAll();

	delete myInstance;
	myInstance = nullptr;
}

RU::Renderer* RU::Renderer::GetInstance()
{
	if (myInstance == nullptr)
	{
		DL_ASSERT("Render Instance does not exists!");
	}
	return myInstance;
}

bool RU::Renderer::Initialize(HGE* aHgeHandler, Syncronizer* aSyncronizer)
{
	if (aHgeHandler == nullptr || aSyncronizer == nullptr)
	{
		return false;
	}
	myHgeHandler = aHgeHandler;
	mySyncronizer = aSyncronizer;

	myRenderBuffers.Init(2);
	CU::GrowingArray<RenderCommand, int> newBuffer;

	myRenderBuffers.Add(newBuffer);
	myRenderBuffers.Add(newBuffer);

	myRenderBuffers[0].Init(128);
	myRenderBuffers[1].Init(128);

	myActiveBuffer = 0;

	return true;
}

void RU::Renderer::AddRenderCommand(const RU::RenderCommand& aRenderCommand)
{
	myRenderBuffers[myActiveBuffer ^ 1].Add(aRenderCommand);
}

void RU::Renderer::SwapBuffers()
{
	myRenderBuffers[myActiveBuffer].RemoveAll();

	myActiveBuffer ^= 1;
}

void RU::Renderer::SetBackgroundColor(const DWORD &aColor)
{
	myBackgroundColor = aColor;
}

void RU::Renderer::Render()
{
	while (mySyncronizer->GetShutDownStatus() == false)
	{
		StartRendering();
		mySyncronizer->WaitForUpdate();
		SwapBuffers();
		mySyncronizer->SetRenderReady();
	}
}

void RU::Renderer::StartRendering()
{
	myHgeHandler->Gfx_BeginScene();

	myHgeHandler->Gfx_Clear(myBackgroundColor);

	//Render Here

	myHgeHandler->Gfx_EndScene();
}

void RU::Renderer::RenderSprite(const Sprite& aSprite)
{
	mySpritesToRender.Add(aSprite);
}