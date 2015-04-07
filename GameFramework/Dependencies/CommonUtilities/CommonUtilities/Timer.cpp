#include "Timer.h"

CU::Timer::Timer()
{
	myPauseCheck = false;
	myID = 0;
	myStartTime.QuadPart = 0;
	myCurrentTime.QuadPart = 0;
	myElapsedTime = 0;
}

CU::Timer::Timer(const unsigned int anID)
{
	myPauseCheck = false;
	myID = anID;
	myStartTime.QuadPart = 0;
	myCurrentTime.QuadPart = 0;
	myElapsedTime = 0;
}

CU::Timer::~Timer()
{

}

void CU::Timer::Start()
{
	myPauseCheck = false;
	QueryPerformanceCounter(&myStartTime);
	QueryPerformanceCounter(&myCurrentTime);
}

void CU::Timer::Pause()
{
	myPauseCheck = true;
}

void CU::Timer::Update(const LARGE_INTEGER &anFrequency)
{

	if (myPauseCheck == false)
	{
		QueryPerformanceCounter(&myCurrentTime);
		myElapsedTime = myCurrentTime.QuadPart - myStartTime.QuadPart;
	}
	myTime.Update(anFrequency, myElapsedTime);
}

bool CU::Timer::IsPaused() const
{
	return myPauseCheck;
}

unsigned int CU::Timer::GetID() const
{
	return myID;
}

const CU::Time& CU::Timer::GetTime() const
{
	return myTime;
}