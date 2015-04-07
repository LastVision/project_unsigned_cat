#include <assert.h>

namespace CommonUtilities
{
	template <typename Type, int Size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray &aStaticArray);
		~StaticArray();

		StaticArray& operator=(const StaticArray &aStaticArray);

		inline const Type& operator[](const int &anIndex) const;
		inline Type& operator[](const int &anIndex);

		inline void Insert(int anIndex, Type &aObject);
		inline void DeleteAll();
	private:
		int mySize = Size + 1;
		Type myData[Size + 1];
	};

	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray()
	{

	}
	template <typename Type, int Size>
	StaticArray<Type, Size>::StaticArray(const StaticArray &aStaticArray)
	{
		this->operator=(aStaticArray);
	}
	template <typename Type, int Size>
	StaticArray<Type, Size>::~StaticArray()
	{

	}
	template <typename Type, int Size>
	StaticArray<Type, Size>& StaticArray<Type, Size>::operator=(const StaticArray &aStaticArray)
	{
		assert(this->mySize == aStaticArray.mySize && "The arrays are not of the same size");
		for (int i = 0; i < this->mySize; ++i)
		{
			myData[i] = aStaticArray.myData[i];
		}
		return *this;
	}
	template <typename Type, int Size>
	inline const Type& StaticArray<Type, Size>::operator[](const int &anIndex) const
	{
		assert((anIndex >= 0 && anIndex < this->mySize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template <typename Type, int Size>
	inline Type& StaticArray<Type, Size>::operator[](const int &anIndex)
	{
		assert((anIndex >= 0 && anIndex < this->mySize) && "Index out of bounds");
		return *(myData + anIndex);
	}
	template <typename Type, int Size>
	inline void StaticArray<Type, Size>::Insert(int anIndex, Type &aObject)
	{
		assert((anIndex >= 0 && anIndex < this->mySize) && "Index out of bounds");
		for (int i = this->mySize - 1; i > anIndex - 1; --i)
		{
			myData[i + 1] = myData[i];
		}
		myData[anIndex] = aObject;
	}
	template <typename Type, int Size>
	inline void StaticArray<Type, Size>::DeleteAll()
	{
		for (int i = 0; i < this->mySize - 1; ++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
	}
} namespace CU = CommonUtilities;