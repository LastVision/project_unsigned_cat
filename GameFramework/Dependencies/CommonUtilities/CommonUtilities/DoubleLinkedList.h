#pragma once
#include "DoubleLinkedListNode.h"
#include <assert.h>

namespace CommonUtilities
{
	/*template <typename Type>
	class DoubleLinkedListNode < Type >;*/

	template<typename Type>
	class DoubleLinkedList
	{
	public:
		DoubleLinkedList();
		~DoubleLinkedList();

		DoubleLinkedListNode<Type>* GetFirstNode();
		DoubleLinkedListNode<Type>* GetLastNode();

		void InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);
		void InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);

		void InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert);
		void InsertNodeSorted(const Type &aValueToInsert);

		void DeleteNode(const Type &aValue);
		void DeleteNode(DoubleLinkedListNode<Type>* aNode);

		DoubleLinkedListNode<Type>* Find(const Type &aValue);
	private:
		DoubleLinkedListNode<Type>* myFirstNode;
		DoubleLinkedListNode<Type>* myLastNode;
	};

	template <typename Type>
	DoubleLinkedList<Type>::DoubleLinkedList()
	{
		myFirstNode = nullptr;
		myLastNode = nullptr;
	}

	template <typename Type>
	DoubleLinkedList<Type>::~DoubleLinkedList()
	{
		for (DoubleLinkedListNode<Type>* i = myFirstNode; i != nullptr;)
		{
			DoubleLinkedListNode<Type>* nextNode = i->myNext;

			delete i;
			i = nullptr;

			i = nextNode;
		}

		myFirstNode = nullptr;
		myLastNode = nullptr;
	}

	template <typename Type>
	DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::GetFirstNode()
	{
		return myFirstNode;
	}

	template <typename Type>
	DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::GetLastNode()
	{
		return myLastNode;
	}

	template <typename Type>
	void DoubleLinkedList<Type>::InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		if (aNode->myPrev == nullptr)
		{
			myFirstNode = aNodeToInsert;
			myFirstNode->myPrev = nullptr;
		}
		else
		{
			aNode->myPrev->myNext = aNodeToInsert;
			aNodeToInsert->myPrev = aNode->myPrev;
		}

		aNodeToInsert->myNext = aNode;
		aNode->myPrev = aNodeToInsert;
		
	}

	template <typename Type>
	void DoubleLinkedList<Type>::InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		if (aNode->myNext == nullptr)
		{
			myLastNode = aNodeToInsert;
			myLastNode->myNext = nullptr;
		}
		else
		{
			aNode->myNext->myPrev = aNodeToInsert;
			aNodeToInsert->myNext = aNode->myNext;
		}
		aNodeToInsert->myPrev = aNode;
		aNode->myNext = aNodeToInsert;
	}

	template <typename Type>
	void DoubleLinkedList<Type>::InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		if (myFirstNode == nullptr)
		{
			myFirstNode = aNodeToInsert;
			myLastNode = myFirstNode;
			return;
		}
		for (DoubleLinkedListNode<Type>* i = myFirstNode; i != nullptr; i = i->myNext)
		{
			if (aNodeToInsert->GetData() >= i->GetData())
			{
				InsertNodeBeforeNode(i, aNodeToInsert);
				return;
			}
			else if (i->myNext == nullptr)
			{
				InsertNodeAfterNode(i, aNodeToInsert);
				return;
			}
		}
	}

	template <typename Type>
	void DoubleLinkedList<Type>::InsertNodeSorted(const Type &aValueToInsert)
	{
		DoubleLinkedListNode<Type>* nodeToInsert = new DoubleLinkedListNode<Type>();
		nodeToInsert->SetData(aValueToInsert);

		if (myFirstNode == nullptr)
		{
			myFirstNode = nodeToInsert;
			myLastNode = myFirstNode;
			return;
		}
		for (DoubleLinkedListNode<Type>* i = myFirstNode; i != nullptr; i = i->myNext)
		{
			if (aValueToInsert >= i->GetData())
			{
				InsertNodeBeforeNode(i, nodeToInsert);
				return;
			}
			else if (i->myNext == nullptr)
			{
				InsertNodeAfterNode(i, nodeToInsert);
				return;
			}
		}
	}

	template <typename Type>
	void DoubleLinkedList<Type>::DeleteNode(const Type &aValue)
	{
		DoubleLinkedListNode<Type>* tempNode = Find(aValue);
		if (tempNode == nullptr)
		{
			assert("This isn't the node you are looking for." && false);
		}
		tempNode->myPrev->myNext = tempNode->myNext;
		tempNode->myNext->myPrev = tempNode->myPrev;

		delete tempNode;
		tempNode = nullptr;
	}

	template <typename Type>
	void DoubleLinkedList<Type>::DeleteNode(DoubleLinkedListNode<Type>* aNode)
	{
		if (aNode == nullptr)
		{
			assert("This isn't the node you are looking for." && false);
		}
		for (DoubleLinkedListNode<Type>* i = myFirstNode; i != nullptr; i = i->myNext)
		{
			if (i == aNode)
			{
				aNode->myPrev->myNext = aNode->myNext;
				aNode->myNext->myPrev = aNode->myPrev;

				delete aNode;
				aNode = nullptr;

				return;
			}
		}
		DL_ASSERT("This isn't the node you are looking for.");
	}

	template <typename Type>
	DoubleLinkedListNode<Type>* DoubleLinkedList<Type>::Find(const Type &aValue)
	{
		for (DoubleLinkedListNode<Type>* i = myFirstNode; i != nullptr; i = i->myNext)
		{
			if (i->GetData() == aValue)
			{
				return i;
			}
		}
		return nullptr;
	}

} namespace CU = CommonUtilities;
//template class CU::DoubleLinkedList < float > ;
//template class CU::DoubleLinkedListNode < float > ;