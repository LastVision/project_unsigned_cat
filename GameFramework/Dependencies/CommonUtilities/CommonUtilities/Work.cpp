#include "Work.h"

CU::Work::Work()
{

}
CU::Work::Work(std::function<void()> aFunctionPointer)
{
	myFunctionPointer = aFunctionPointer;
}
CU::Work::~Work()
{

}
void CU::Work::DoWork()
{
	myFunctionPointer();
}
std::function<void()> CU::Work::GetFunctionPointer()
{
	return myFunctionPointer;
}