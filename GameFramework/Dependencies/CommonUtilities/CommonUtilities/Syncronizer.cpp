#include "Syncronizer.h"
#include <thread>

Syncronizer::Syncronizer()
{
	myUpdateDone = false;
	myRenderDone = false;
	myShutDown = false;
}
Syncronizer::~Syncronizer()
{

}

void Syncronizer::WaitForUpdate()
{
	while (myUpdateDone == false && myShutDown == false)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}

	myUpdateDone = false;
}
void Syncronizer::WaitForRender()
{
	while (myRenderDone == false && myShutDown == false)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}

	myRenderDone = false;
}

void Syncronizer::SetUpdateReady()
{
	myUpdateDone = true;
}
void Syncronizer::SetRenderReady()
{
	myRenderDone = true;
}

void Syncronizer::ShutDownThreads()
{
	myShutDown = true;
}

bool Syncronizer::GetShutDownStatus() const
{
	return myShutDown;
}