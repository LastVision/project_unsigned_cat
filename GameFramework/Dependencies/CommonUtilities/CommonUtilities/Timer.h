#pragma once
#include "Time.h"
namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const unsigned int anID);
		~Timer();

		void Start();
		void Pause();
		void Update(const LARGE_INTEGER &anFrequency);

		bool IsPaused() const;

		unsigned int GetID() const;
		const Time& GetTime() const;
	private:
		LARGE_INTEGER myStartTime;
		LARGE_INTEGER myCurrentTime;

		long long myElapsedTime;
		unsigned int myID;
		bool myPauseCheck;
		Time myTime;
	};
}namespace CU = CommonUtilities;