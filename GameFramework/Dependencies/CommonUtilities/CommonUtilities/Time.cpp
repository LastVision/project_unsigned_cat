#include "Time.h"

CU::Time::Time()
{

}

CU::Time::~Time()
{

}

void CU::Time::Update(const LARGE_INTEGER &anFrequency, const long long anDeltaTime)
{
	myMicroSeconds = anDeltaTime;
	myMilliSeconds = anDeltaTime;
	mySeconds = anDeltaTime;
	myMinutes = anDeltaTime;
	myHours = anDeltaTime;

	myMicroSeconds *= 1000000;
	myMilliSeconds *= 1000;
	myMinutes /= 60;
	myHours /= 3600;

	myMicroSeconds /= anFrequency.QuadPart;
	myMilliSeconds /= anFrequency.QuadPart;
	mySeconds /= anFrequency.QuadPart;
	myMinutes /= anFrequency.QuadPart;
	myHours /= anFrequency.QuadPart;
}

long long CU::Time::GetMicroSeconds() const
{
	return myMicroSeconds;
}

long long CU::Time::GetMilliSeconds() const
{
	return myMilliSeconds;
}

long long CU::Time::GetSeconds() const
{
	return mySeconds;
}

long long CU::Time::GetMinutes() const
{
	return myMinutes;
}

long long CU::Time::GetHours() const
{
	return myHours;
}