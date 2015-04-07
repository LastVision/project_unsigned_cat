#include "TimerManager.h"

CU::TimerManager::TimerManager()
{
	QueryPerformanceFrequency(&myFrequency);
	myMasterTimer.Start();
}

CU::TimerManager::~TimerManager()
{

}

int CU::TimerManager::CreateTimer()
{
	unsigned int id = 0;
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		if (myTimers.at(0).GetID() == id)
		{
			++id;
		}
		else if (myTimers.at(i).GetID() == id)
		{
			++id;
			i = 0;
		}
	}
	Timer timer(id);
	timer.Start();

	myTimers.push_back(timer);
	return id;
}

void CU::TimerManager::RemoveTimer(const unsigned int anIndex)
{
	assert((anIndex > 0 || anIndex < myTimers.size()) && "The index was out of bounds on myTimers vector!");
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		if (myTimers.at(i).GetID() == anIndex)
		{
			myTimers.erase(myTimers.begin() + anIndex);
		}
	}
}

void CU::TimerManager::StartTimer(const unsigned int anIndex)
{
	assert((anIndex > 0 || anIndex < myTimers.size()) && "The index was out of bounds on myTimers vector!");
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		if (myTimers.at(i).GetID() == anIndex)
		{
			myTimers.at(i).Start();
		}
	}
}

void CU::TimerManager::PauseTimer(const unsigned int anIndex)
{
	assert((anIndex > 0 || anIndex < myTimers.size()) && "The index was out of bounds on myTimers vector!");
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		if (myTimers.at(i).GetID() == anIndex)
		{
			myTimers.at(i).Pause();
		}
	}
}

void CU::TimerManager::StartTimers()
{
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		myTimers.at(i).Start();
	}
}

void CU::TimerManager::PauseTimers()
{
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		myTimers.at(i).Pause();
	}
}

void CU::TimerManager::UpdateTimers()
{
	myLastTick.QuadPart = myCurrentTick.QuadPart;
	QueryPerformanceFrequency(&myFrequency);
	QueryPerformanceCounter(&myCurrentTick);

	myDeltaTime.QuadPart = myCurrentTick.QuadPart - myLastTick.QuadPart;
	myDeltaTime.QuadPart *= 1000000;
	myDeltaTime.QuadPart /= myFrequency.QuadPart;

	myFrameTime = static_cast<float>(myDeltaTime.QuadPart) / myFrequency.QuadPart;
	myFPS = static_cast<int>(1 / myFrameTime);

	myMasterTimer.Update(myFrequency);
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		myTimers.at(i).Update(myFrequency);
	}
}

void CU::TimerManager::PrintAllTimers()
{
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		PrintTimer(i);
	}
}

void CU::TimerManager::PrintTimer(const unsigned int anIndex)
{
	assert((anIndex > 0 || anIndex < myTimers.size()) && "The index was out of bounds on myTimers vector!");
	std::cout << "----------Timer----------" << std::endl;
	std::cout << "ID: " << myTimers.at(anIndex).GetID() << std::endl;
	std::cout << "Hours: " << myTimers.at(anIndex).GetTime().GetHours() << std::endl;
	std::cout << "Minutes: " << myTimers.at(anIndex).GetTime().GetMinutes() << std::endl;
	std::cout << "Seconds: " << myTimers.at(anIndex).GetTime().GetSeconds() << std::endl;
	std::cout << "Milliseconds: " << myTimers.at(anIndex).GetTime().GetMilliSeconds() << std::endl;
	std::cout << "Microseconds: " << myTimers.at(anIndex).GetTime().GetMicroSeconds() << std::endl;
}

void CU::TimerManager::PrintMasterTimer()
{
	std::cout << "----------Master Timer----------" << std::endl;
	std::cout << "ID: " << myMasterTimer.GetID() << std::endl;
	std::cout << "Hours: " << myMasterTimer.GetTime().GetHours() << std::endl;
	std::cout << "Minutes: " << myMasterTimer.GetTime().GetMinutes() << std::endl;
	std::cout << "Seconds: " << myMasterTimer.GetTime().GetSeconds() << std::endl;
	std::cout << "Milliseconds: " << myMasterTimer.GetTime().GetMilliSeconds() << std::endl;
	std::cout << "Microseconds: " << myMasterTimer.GetTime().GetMicroSeconds() << std::endl;
}

const CU::Timer& CU::TimerManager::GetTimer(const unsigned int anIndex) const
{
	assert((anIndex > 0 || anIndex < myTimers.size()) && "The index was out of bounds on myTimers vector!");
	for (unsigned int i = 0; i < myTimers.size(); ++i)
	{
		if (myTimers.at(i).GetID() == anIndex)
		{
			return myTimers.at(i);
		}
	}
	return myMasterTimer;
}

const CU::Timer& CU::TimerManager::GetMasterTimer() const
{
	return myMasterTimer;
}

int CU::TimerManager::GetFPS() const
{
	return myFPS;
}

float CU::TimerManager::GetFrameTime() const
{
	return myFrameTime;
}

float CU::TimerManager::GetDeltaTime() const
{
	return static_cast<float>(myDeltaTime.QuadPart) / 1000000;
}