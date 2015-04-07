#pragma once
#include <Window\Window.h>
#include <InputHandler.h>
class Game : public Window
{
public:
	Game();
	~Game();
private:
	bool Update() override;
	void Init() override;
private:
	
};

