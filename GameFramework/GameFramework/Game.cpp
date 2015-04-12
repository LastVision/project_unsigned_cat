#include "Game.h"
#include <Renderer\Renderer.h>


Game::Game()
{
	
}

Game::~Game()
{
	
}

void Game::Init()
{
	RU::Renderer::GetInstance()->RU::Renderer::SetBackgroundColor(0xFF0000FF);
	
}

bool Game::Update()
{
	std::string ss;
	if (myInput.GetKeyDown(DIK_R) == true)
	{
		RU::Renderer::GetInstance()->RU::Renderer::SetBackgroundColor(0xFFFF0000);
		ss = "Red ";
	}
	else if (myInput.GetKeyDown(DIK_G) == true)
	{
		RU::Renderer::GetInstance()->RU::Renderer::SetBackgroundColor(0xFF00FF00);
		ss = "Green ";
	}
	else if (myInput.GetKeyDown(DIK_B) == true)
	{
		RU::Renderer::GetInstance()->RU::Renderer::SetBackgroundColor(0xFFFF00FF);
		ss = "Pink ";
	}
	else if (myInput.GetKeyDown(DIK_ESCAPE) == true)
	{
		myWindowRunning = false;
	}
	else
	{
		ss = "None ";
	}
	ss += "was pressed\n";
	ss += "Delta Time: " + std::to_string(myDeltaTime) + "\n";
	ss += "FPS: " + std::to_string(myFramePerSecond) + "\n";
	OutputDebugStringA(ss.c_str());
	return true;
}
