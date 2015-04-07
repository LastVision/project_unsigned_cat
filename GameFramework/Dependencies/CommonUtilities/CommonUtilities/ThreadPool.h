#pragma once
#include "Worker.h"
#include "GrowingArray.h"
#include <queue>
#include <thread>
namespace CommonUtilities
{
	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();
		void AddWork(const Work& someWork);
		void Update();
	private:
		void AssignWork();
		CU::GrowingArray<CU::Worker> myWorkers;
		std::queue<Work> myWork;
	};
} namespace CU = CommonUtilities;