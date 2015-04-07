#pragma once
#include <thread>
#include "Work.h"
#include "GrowingArray.h"
namespace CommonUtilities
{
	class Worker
	{
	public:
		Worker();
		~Worker();
		void Init();
		void AssignWork(Work someWork);
		bool IsWorking() const;
	private:
		void Update();
		volatile bool myIsWorking;
		bool myIsExisting;

		std::thread* myThread;
		CU::GrowingArray<Work> myWork;
	};
} namespace CU = CommonUtilities;