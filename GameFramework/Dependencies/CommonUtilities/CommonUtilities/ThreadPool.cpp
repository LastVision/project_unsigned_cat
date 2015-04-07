#include "ThreadPool.h"


CU::ThreadPool::ThreadPool()
{
	myWorkers.Init(10);
	int numberOfThreads = std::thread::hardware_concurrency();
	for (unsigned short i = 0; i < numberOfThreads; ++i)
	{
		myWorkers.Add(Worker());
		myWorkers[i].Init();
	}
}

CU::ThreadPool::~ThreadPool()
{

}

void CU::ThreadPool::Update()
{
	AssignWork();
}

void CU::ThreadPool::AddWork(const Work& someWork)
{
	myWork.push(someWork);
}

void CU::ThreadPool::AssignWork()
{
	while(myWork.empty() == false)
	{
		for (unsigned short i = 0; i < myWorkers.Size(); ++i)
		{
			if (myWorkers[i].IsWorking() == false)
			{
				myWorkers[i].AssignWork(myWork.back());
				myWork.pop();
				break;
			}
		}
	}
}