#pragma once
#include <functional>
namespace CommonUtilities
{
	class Work
	{
	public:
		Work();
		Work(std::function<void()> aFunctionPointer);
		~Work();
		void DoWork();
		std::function<void()> GetFunctionPointer();
	private:
		std::function<void()> myFunctionPointer;
	};

} namespace CU = CommonUtilities;