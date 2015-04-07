#pragma once

namespace CommonUtilities
{
	template <typename Type>
	class DoubleLinkedList;

	template <typename Type>
	class DoubleLinkedListNode
	{
		friend class DoubleLinkedList < Type > ;
	public:
		DoubleLinkedListNode();
		DoubleLinkedListNode(Type aData);
		DoubleLinkedListNode(DoubleLinkedListNode* aPrev, DoubleLinkedListNode* aNext);
		~DoubleLinkedListNode();

		Type GetData();
		void SetData(const Type &aValue);
	private:
		DoubleLinkedListNode* myNext;
		DoubleLinkedListNode* myPrev;
		Type myData;
	};
	template <typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode()
	{

	}
	template <typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode(Type aData)
	{
		myData = aData;
	}
	template <typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode(DoubleLinkedListNode* aPrev, DoubleLinkedListNode* aNext)
	{
		myNext = aNext;
		myPrev = aPrev;
	}
	template <typename Type>
	DoubleLinkedListNode<Type>::~DoubleLinkedListNode()
	{

	}
	template <typename Type>
	Type DoubleLinkedListNode<Type>::GetData()
	{
		return myData;
	}
	template <typename Type>
	void DoubleLinkedListNode<Type>::SetData(const Type &aValue)
	{
		myData = aValue;
	}
} namespace CU = CommonUtilities;