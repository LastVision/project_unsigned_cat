#pragma once
#include "Timer.h"
#include <vector>
namespace CommonUtilities
{
	class TimerManager
	{
	public:
		TimerManager();
		~TimerManager();

		int CreateTimer();
		void RemoveTimer(const unsigned int anIndex);
		void StartTimer(const unsigned int anIndex);
		void PauseTimer(const unsigned int anIndex);

		void StartTimers();
		void PauseTimers();
		void UpdateTimers();

		void PrintAllTimers();
		void PrintTimer(const unsigned int anIndex);
		void PrintMasterTimer();

		const Timer& GetTimer(const unsigned int anIndex) const;
		const Timer& GetMasterTimer() const;

		int GetFPS() const;
		float GetFrameTime() const;
		float GetDeltaTime() const;
	private:
		Timer myMasterTimer;
		std::vector<Timer> myTimers;

		LARGE_INTEGER myFrequency;
		LARGE_INTEGER myCurrentTick;
		LARGE_INTEGER myLastTick;

		int myFPS;
		float myFrameTime;
		LARGE_INTEGER myDeltaTime;
	};
}namespace CU = CommonUtilities;