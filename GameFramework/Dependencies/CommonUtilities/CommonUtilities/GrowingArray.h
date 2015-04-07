#pragma once
#include <assert.h>
namespace CommonUtilities
{
	template <typename ObjectType, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);

		void Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		void ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);

		inline ObjectType& operator[](const SizeType& aIndex);
		inline const ObjectType& operator[](const SizeType& aIndex) const;

		inline void Add(const ObjectType& aObject);
		inline void Insert(SizeType aIndex, ObjectType& aObject);
		inline void DeleteCyclic(ObjectType& aObject);
		inline void DeleteCyclicAtIndex(SizeType aItemNumber);
		inline void RemoveCyclic(const ObjectType& aObject);
		inline void RemoveCyclicAtIndex(SizeType aItemNumber);
		inline SizeType Find(const ObjectType& aObject);

		inline ObjectType& GetLast();
		inline const ObjectType& GetLast() const;

		static const int FoundNone = -1;

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline int Size() const;
	private:
		inline void Resize(SizeType aNewSize);

		SizeType myCurrentSize;
		SizeType myAlocatedSize;
		ObjectType *myData;
		bool myUseSafeModeFlag;
	};

	template <typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray()
	{
		myCurrentSize = 0;
		myAlocatedSize = 0;
		myUseSafeModeFlag = true;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		myAlocatedSize = aNrOfRecomendedItems;
		myCurrentSize = 0;
		myUseSafeModeFlag = aUseSafeModeFlag;
		myData = new ObjectType[myAlocatedSize + 1];
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray &aGrowingArray)
	{
		*this = aGrowingArray;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>::~GrowingArray()
	{
		if (myData != nullptr)
		{
			delete[] myData;
			myData = nullptr;
		}
		myCurrentSize = 0;
		myAlocatedSize = 0;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray &aGrowingArray)
	{
		myCurrentSize = aGrowingArray.myCurrentSize;
		myAlocatedSize = aGrowingArray.myAlocatedSize;
		myData = new ObjectType[myAlocatedSize];
		myUseSafeModeFlag = aGrowingArray.myUseSafeModeFlag;
		if (myUseSafeModeFlag == true)
		{
			for (SizeType i = 0; i < aGrowingArray.myCurrentSize; ++i)
			{
				this->myData[i] = aGrowingArray.myData[i];
			}
		}
		else
		{
			memcpy(this->myData, aGrowingArray.myData, sizeof(ObjectType) * aGrowingArray.myAlocatedSize);
		}		
		return *this;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		myCurrentSize = 0;
		myAlocatedSize = aNrOfRecomendedItems;
		myUseSafeModeFlag = aUseSafeModeFlag;
		myData = new ObjectType[myAlocatedSize];
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::ReInit(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag)
	{
		delete[] myData;
		myCurrentSize = 0;
		myAlocatedSize = aNrOfRecommendedItems;
		myUseSafeModeFlag = aUseSafeModeFlag;
		myData = new ObjectType[myAlocatedSize];
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType &anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->myCurrentSize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline const ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType &anIndex) const
	{
		assert((anIndex >= 0 && anIndex <= this->myCurrentSize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::Add(const ObjectType &aObject)
	{
		if (myCurrentSize >= myAlocatedSize)
		{
			Resize(myAlocatedSize * 2);
		}
		myData[myCurrentSize] = aObject;
		++myCurrentSize;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::Insert(SizeType anIndex, ObjectType &aObject)
	{
		assert((anIndex >= 0 && anIndex <= this->myCurrentSize) && "Index out of bounds");
		if (myCurrentSize >= myAlocatedSize)
		{
			Resize(myAlocatedSize * 2);
		}
		for (SizeType i = this->myCurrentSize; i > anIndex; --i)
		{
			myData[i] = myData[i-1];
		}
		myData[anIndex] = aObject;
		++myCurrentSize;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclic(ObjectType &aObject)
	{
		for (SizeType i = 0; i < myAlocatedSize; ++i)
		{
			if (this->myData[i] == aObject)
			{
				delete myData[i];
				myData[i] = nullptr;
				myData[i] = myData[myCurrentSize - 1];
				delete myData[myCurrentSize - 1];
				myData[myCurrentSize - 1] = nullptr;
				--myCurrentSize;
				return;
			}
		}
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclicAtIndex(SizeType anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->myCurrentSize) && "Index out of bounds");
		delete myData[anIndex];
		myData[anIndex] = nullptr;
		myData[anIndex] = myData[myCurrentSize - 1];
		delete myData[myCurrentSize - 1];
		myData[myCurrentSize - 1] = nullptr;
		--myCurrentSize;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType &aObject)
	{
		for (SizeType i = 0; i < myAlocatedSize; ++i)
		{
			if (this->myData[i] == aObject)
			{
				myData[i] = myData[myCurrentSize - 1];
				--myCurrentSize;
				return;
			}
		}
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->myCurrentSize) && "Index out of bounds");
		myData[anIndex] = myData[myCurrentSize - 1];
		--myCurrentSize;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline SizeType GrowingArray<ObjectType, SizeType>::Find(const ObjectType &aObject)
	{
		for (SizeType i = 0; i < myCurrentSize; ++i)
		{
			if (myData[i] == aObject)
			{
				return i;
			}
		}
		return FoundNone;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline ObjectType& GrowingArray<ObjectType, SizeType>::GetLast()
	{
		return myData[myCurrentSize - 1];
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline const ObjectType& GrowingArray<ObjectType, SizeType>::GetLast() const
	{
		return myData[myCurrentSize - 1];
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAll()
	{
		myCurrentSize = 0;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::DeleteAll()
	{
		for (SizeType i = 0; i < myCurrentSize - 1; ++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
		myCurrentSize = 0;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	void GrowingArray<ObjectType, SizeType>::Optimize()
	{
		Resize(myCurrentSize);
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	__forceinline int GrowingArray<ObjectType, SizeType>::Size() const
	{
		return myCurrentSize;
	}
	template <typename ObjectType, typename SizeType = unsigned short>
	inline void GrowingArray<ObjectType, SizeType>::Resize(SizeType aNewSize)
	{
		assert((aNewSize > 0) && "You tried to resize the vector below 0");
		ObjectType *tempData = new ObjectType[aNewSize];
		for (SizeType i = 0; i < myCurrentSize; ++i)
		{
			tempData[i] = myData[i];
		}
		delete[] myData;
		myData = tempData;
		myAlocatedSize = aNewSize;
	}
}namespace CU = CommonUtilities;

//template class CU::GrowingArray<int*, int>;