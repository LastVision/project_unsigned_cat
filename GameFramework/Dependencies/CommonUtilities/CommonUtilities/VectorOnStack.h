#include <assert.h>

namespace CommonUtilities
{
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);

		~VectorOnStack();

		VectorOnStack & operator=(const VectorOnStack & aVectorOnStack);

		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);

		inline void Clear();
		inline void DeleteAll();

		__forceinline CountType GetSize() const;
	private:
		CountType myCounter;
		int mySize;
		Type myData[Size];
		bool myUseSafeModeFlag;
	};
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		mySize = Size;
		myCounter = 0;
		myUseSafeModeFlag = UseSafeModeFlag;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack &aVectorOnStack)
	{
		mySize = aVectorOnStack.mySize;
		myCounter = 0;
		myUseSafeModeFlag = aVectorOnStack.myUseSafeModeFlag;
		this->operator=(aVectorOnStack);
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		mySize = 0;
		myCounter = 0;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	VectorOnStack<Type, Size, CountType, UseSafeModeFlag>& VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::operator=(const VectorOnStack &aVectorOnStack)
	{
		assert(this->mySize == aVectorOnStack.mySize && "The arrays are not of the same size");
		myUseSafeModeFlag = aVectorOnStack.myUseSafeModeFlag;
		mySize = aVectorOnStack.mySize;
		if (myUseSafeModeFlag == true)
		{
			for (int i = 0; i < this->mySize; ++i)
			{
				this->myData[i] = aVectorOnStack.myData[i];
			}
		}
		else
		{
			memcpy(this->myData, aVectorOnStack.myData, sizeof(aVectorOnStack.myData));
		}
		myCounter = aVectorOnStack.myCounter;
		return *this;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline const Type& VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::operator[](const CountType &anIndex) const
	{
		assert((anIndex >= 0 && anIndex <= this->mySize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline Type& VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::operator[](const CountType &anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->mySize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::Add(const Type &aObject)
	{
		assert(myCounter <= mySize && "Vector is at maximum capacity");
		myData[myCounter] = aObject;
		++myCounter;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::Insert(CountType anIndex, Type &aObject)
	{
		assert((anIndex >= 0 && anIndex <= this->myCounter) && "Index out of bounds");
		for (int i = this->mySize - 1; i > anIndex - 1; --i)
		{
			myData[i + 1] = myData[i];
		}
		myData[anIndex] = aObject;
		++myCounter;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::DeleteCyclic(Type &aObject)
	{
		for (int i = 0; i < mySize; ++i)
		{
			if (this->myData[i] == aObject)
			{
				delete myData[i];
				myData[i] = nullptr;
				myData[i] = myData[myCounter - 1];
				delete myData[myCounter - 1];
				myData[myCounter - 1] = nullptr;
				--myCounter;
				return;
			}
		}
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->myCounter) && "Index out of bounds");
		delete myData[anIndex];
		myData[anIndex] = nullptr;
		myData[anIndex] = myData[myCounter - 1];
		delete myData[myCounter - 1];
		myData[myCounter - 1] = nullptr;
		--myCounter;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::RemoveCyclic(const Type &aObject)
	{
		bool foundObject = false;
		for (int i = 0; i < mySize; ++i)
		{
			if (this->myData[i] == aObject)
			{
				foundObject = true;
				myData[i] = myData[myCounter - 1];
				--myCounter;
				return;
			}
		}
		assert(foundObject == true && "Object not found!");
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType anIndex)
	{
		assert((anIndex >= 0 && anIndex <= this->myCounter) && "Index out of bounds");
		myData[anIndex] = myData[myCounter - 1];
		--myCounter;

	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::Clear()
	{
		myCounter = 0;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	inline void VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (int i = 0; i < myCounter; ++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
		myCounter = 0;
	}
	template<typename Type, int Size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	__forceinline CountType VectorOnStack<Type, Size, CountType, UseSafeModeFlag>::GetSize() const
	{
		return this->myCounter;
	}

} namespace CU = CommonUtilities;