#pragma once
#include <Windows.h>
#include <iostream>
#include <assert.h>
namespace CommonUtilities
{
	class Time
	{
	public:
		Time();
		~Time();

		void Update(const LARGE_INTEGER &anFrequency, const long long anDeltaTime);

		long long GetMicroSeconds() const;
		long long GetMilliSeconds() const;
		long long GetSeconds() const;
		long long GetMinutes() const;
		long long GetHours() const;
	private:
		long long myMicroSeconds;
		long long myMilliSeconds;
		long long mySeconds;
		long long myMinutes;
		long long myHours;
	};
}namespace CU = CommonUtilities;