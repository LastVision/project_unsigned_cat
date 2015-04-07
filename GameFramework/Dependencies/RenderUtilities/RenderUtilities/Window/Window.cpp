#include "Window.h"
#include <DL_Debug.h>
#include "../Sprite/Sprite.h"
#include "../Renderer/Renderer.h"

Window::Window()
{
	myHgeHandler = nullptr;
	myWindowRunning = false;
}

Window::~Window()
{
	Shutdown();
	Release();
}

void Window::Shutdown()
{
	
}

void Window::Release()
{
	mySyncronizer->ShutDownThreads();

	myHgeHandler->System_Shutdown();
	myHgeHandler->Release();

	RU::Renderer::Destroy();
	DL_DEBUG::Debug::Destroy();
}

bool Window::Initialize()
{
	if (InitializeHge() == false)
	{
		return false;
	}
	mySyncronizer = new Syncronizer();

	DL_DEBUG::Debug::Create("../../Debug/Debug.log");

	RU::Renderer::Create(myHgeHandler, mySyncronizer);
	RU::Renderer::GetInstance()->SetBackgroundColor(0xFF6644D5);

	Init();

	myThreadPool.AddWork(CU::Work([&]
	{
		RU::Renderer::GetInstance()->Render();
	}));
	return true;
}

void Window::Init()
{

}

void Window::Run()
{
	myWindowRunning = Initialize();
	myInput.Init(GetModuleHandle(nullptr));
	myTimer.StartTimers();
	
	while (mySyncronizer->GetShutDownStatus() == false && myWindowRunning == true)
	{
		myThreadPool.Update();
		MSG myMSG;
		if (PeekMessage(&myMSG, NULL, 0, 0, PM_REMOVE))
		{
			if (myMSG.message == WM_QUIT)
			{
				myWindowRunning = false;
				return;
			}
			DispatchMessage(&myMSG);
		}
		myTimer.UpdateTimers();
		myDeltaTime = myTimer.GetDeltaTime();
		myFramePerSecond = myTimer.GetFPS();

		myInput.Update(myDeltaTime);

		Update();
		mySyncronizer->SetUpdateReady();

		mySyncronizer->WaitForRender();
	};
}

bool Window::Update()
{
	return myWindowRunning;
}

bool Window::InitializeHge()
{
	myHgeHandler = hgeCreate(HGE_VERSION);
	myHgeHandler->System_SetState(HGE_WINDOWED, true);
	myHgeHandler->System_SetState(HGE_USESOUND, false);
	myHgeHandler->System_SetState(HGE_SCREENWIDTH, 755);
	myHgeHandler->System_SetState(HGE_SCREENHEIGHT, 600);
	myHgeHandler->System_SetState(HGE_SCREENBPP, 32);
	myHgeHandler->System_SetState(HGE_SHOWSPLASH, true);
	myHgeHandler->System_SetState(HGE_TITLE, "Empty Project");
	/*myHgeHandler->System_SetState(HGE_FPS, HGEFPS_VSYNC);*/

	if (myHgeHandler->System_Initiate())
	{
		myHgeHandler->System_Start();
	}
	else
	{
		MessageBox(nullptr, myHgeHandler->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return false;
	}
	return true;
}