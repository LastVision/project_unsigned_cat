#include "Worker.h"
#include<iostream>

CU::Worker::Worker()
{
	myIsWorking = false;
	myIsExisting = true;
	myThread = nullptr;
	
	myWork.Init(4);
}

CU::Worker::~Worker()
{
	myIsExisting = false;
	if (myThread != nullptr)
	{
		myThread->join();
		delete myThread;
		myThread = nullptr;
	}
}

void CU::Worker::Init()
{
	myThread = new std::thread(&Worker::Update, std::ref(*this));
}

void CU::Worker::AssignWork(CU::Work someWork)
{
	myIsWorking = true;
	myWork.Add(someWork);
}

bool CU::Worker::IsWorking() const
{
	return myIsWorking;
}

void CU::Worker::Update()
{
	while (myIsExisting == true)
	{
		if (myWork.Size() < 1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			for (unsigned short i = 0; i < myWork.Size(); ++i)
			{
				myWork[i].DoWork();
				//std::cout << "Work Done!" << std::endl;
				myWork.RemoveCyclicAtIndex(i);
			}
			myIsWorking = false;
		}
	}
}