#pragma once
#include "Plane.h"
#include "Vector.h"
#include "GrowingArray.h"

namespace CommonUtilities
{
	template <typename Type>
	class PlaneVolume
	{
	public:
		PlaneVolume();
		PlaneVolume(GrowingArray<Plane<Type>> aPlaneList);
		~PlaneVolume();
		void AddPlane(Plane<Type> aPlane);
		void RemovePlane(Plane<Type> aPlane);
		bool Inside(Vector3<Type> aPosition);
		bool Inside(const Vector3<Type>& aPosition) const;
		const GrowingArray<Plane<Type>>& GetPlaneList() const;

	private:
		GrowingArray<Plane<Type>> myPlaneList;
	};
	template <typename Type>
	PlaneVolume<Type>::PlaneVolume()
	{
		myPlaneList.Init(1);
	}
	template <typename Type>
	PlaneVolume<Type>::PlaneVolume(GrowingArray<Plane<Type>> aPlaneList)
	{
		myPlaneList = aPlaneList;
	}
	template <typename Type>
	PlaneVolume<Type>::~PlaneVolume()
	{

	}
	template <typename Type>
	void PlaneVolume<Type>::AddPlane(Plane<Type> aPlane)
	{
		myPlaneList.Add(aPlane);
	}
	template <typename Type>
	void PlaneVolume<Type>::RemovePlane(Plane<Type> aPlane)
	{
		myPlaneList.RemoveCyclic(aPlane);
	}
	template <typename Type>
	bool PlaneVolume<Type>::Inside(Vector3<Type> aPosition)
	{
		for (unsigned short i = 0; i < myPlaneList.Size(); ++i)
		{
			if (myPlaneList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}

	template <typename Type>
	bool PlaneVolume<Type>::Inside(const Vector3<Type>& aPosition) const
	{
		for (unsigned short i = 0; i < myPlaneList.Size(); ++i)
		{
			if (myPlaneList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}
	template <typename Type>
	const GrowingArray<Plane<Type>>& PlaneVolume<Type>::GetPlaneList() const
	{
		return myPlaneList;
	}
}
namespace CU = CommonUtilities;
//template class CU::PlaneVolume < int > ;
//template class CU::Plane < int > ;