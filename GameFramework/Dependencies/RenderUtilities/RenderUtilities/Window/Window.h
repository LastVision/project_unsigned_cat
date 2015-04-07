#pragma once
#include <Syncronizer.h>
#include <hge.h>
#include <ThreadPool.h>
#include <InputHandler.h>
#include <TimerManager.h>

class Window
{
public:
	Window();
	~Window();

	void Run();
protected:
	virtual bool Update();
	virtual void Shutdown();
	virtual void Init();
private:
	bool Initialize();
	void InitializeRenderer();
	bool InitializeHge();
	void Release();
protected:
	HGE* myHgeHandler;

	float myDeltaTime;
	int myFramePerSecond;

	CU::InputHandler myInput;
	CU::ThreadPool myThreadPool;

	bool myWindowRunning;
private:
	Syncronizer* mySyncronizer;
	CU::TimerManager myTimer;

};