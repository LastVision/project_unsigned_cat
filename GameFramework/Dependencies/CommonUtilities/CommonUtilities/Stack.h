#pragma once
#include "GrowingArray.h"
namespace CommonUtilities
{
	template<typename Type>
	class Stack
	{
	public:
		Stack();
		Stack(const int aInitSize);
		~Stack();

		void Init(const int aInitSize);
		void ReInit(const int aInitSize);

		Type Pop();
		Type Top();
		int Size();
		void Push(const Type& aValue);
	private:
		CU::GrowingArray<Type, int> myData;
	};

	template<typename Type>
	Stack<Type>::Stack()
	{
		
	}

	template<typename Type>
	Stack<Type>::Stack(const int aInitSize)
	{
		Init(aInitSize);
	}

	template<typename Type>
	Stack<Type>::~Stack()
	{
		myData.~GrowingArray();
	}

	template<typename Type>
	void Stack<Type>::Init(const int aInitSize)
	{
		myData.Init(aInitSize);
	}

	template<typename Type>
	void Stack<Type>::ReInit(const int aInitSize)
	{
		myData.ReInit(aInitSize);
	}

	template<typename Type>
	Type Stack<Type>::Pop()
	{
		assert((myData.Size() > 0) && "Trying to pop below zero");
		Type dataToReturn = myData.GetLast();
		myData.RemoveCyclicAtIndex(myData.Size());
		return dataToReturn;
	}

	template<typename Type>
	Type Stack<Type>::Top()
	{
		assert((myData.Size() > 0) && "Trying to top below zero");
		return myData.GetLast();
	}

	template<typename Type>
	void Stack<Type>::Push(const Type& aValue)
	{
		myData.Add(aValue);
	}

	template<typename Type>
	int Stack<Type>::Size()
	{
		return static_cast<int>(myData.Size());
	}

}namespace CU = CommonUtilities;

//template class CU::Stack < int > ;