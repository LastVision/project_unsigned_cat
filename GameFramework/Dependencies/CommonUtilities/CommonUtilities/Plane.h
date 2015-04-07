#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	template<typename Type>
	class Plane
	{
	public:
		Plane();
		Plane(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint);
		Plane(Vector3<Type> aPoint, Vector3<Type> aNormal);
		~Plane();
		bool operator==(const Plane<Type> &aPlane);
		void InitWith3Pointers(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint);
		void InitWithPointAndNormal(Vector3<Type> aPoint, Vector3<Type> aNormal);
		bool Inside(Vector3<Type> aPosition);
		bool Inside(Vector3<Type> aPosition) const;
		Vector3<Type> GetNormal() const;
		Vector4<Type> GetAbcd() const;
	private:
		Vector3<Type> myNormal;
		Vector4<Type> myAbcd;
	};

	template<typename Type>
	Plane<Type>::Plane()
	{
		myAbcd.myX = 0;
		myAbcd.myY = 0;
		myAbcd.myZ = 0;
		myAbcd.myW = 0;
	}
	template<typename Type>
	Plane<Type>::Plane(Vector3<Type> aFirstPoint, Vector3<Type>aSecondPoint, Vector3<Type> aThirdPoint)
	{
		Vector3<Type> tempNormal;
		tempNormal = Cross(aSecondPoint - aFirstPoint, aThirdPoint - aFirstPoint);
		Normalize(tempNormal);
		myNormal = tempNormal;
		myAbcd.myX = tempNormal.myX;
		myAbcd.myY = tempNormal.myY;
		myAbcd.myZ = tempNormal.myZ;
		myAbcd.myW = Dot(tempNormal, aThirdPoint);
	}
	template<typename Type>
	Plane<Type>::Plane(Vector3<Type> aPoint, Vector3<Type> aNormal)
	{
		myAbcd.myX = aNormal.myX;
		myAbcd.myY = aNormal.myY;
		myAbcd.myZ = aNormal.myZ;
		myAbcd.myW = Dot(aPoint, aNormal);
		myNormal = aNormal;
	}
	template<typename Type>
	Plane<Type>::~Plane()
	{

	}
	template<typename Type>
	bool Plane<Type>::operator==(const Plane<Type> &aPlane)
	{
		if (myAbcd == aPlane.myAbcd)
		{
			return true;
		}
		return false;
	}
	template<typename Type>
	void Plane<Type>::InitWith3Pointers(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint)
	{
		Vector3<Type> tempNormal;
		tempNormal = Cross(aSecondPoint - aFirstPoint, aThirdPoint - aFirstPoint);
		Normalize(tempNormal);
		myAbcd.myX = tempNormal.myX;
		myAbcd.myY = tempNormal.myY;
		myAbcd.myZ = tempNormal.myZ;
		myAbcd.myW = Dot(tempNormal, aThirdPoint);
	}
	template<typename Type>
	void Plane<Type>::InitWithPointAndNormal(Vector3<Type> aPoint, Vector3<Type> aNormal)
	{
		myAbcd.myX = aNormal.myX;
		myAbcd.myY = aNormal.myY;
		myAbcd.myZ = aNormal.myZ;
		myAbcd.myW = Dot(aPoint, aNormal);
	}
	template<typename Type>
	bool Plane<Type>::Inside(Vector3<Type> aPosition)
	{
		Vector3<Type> tempPoint;
		tempPoint.myX = myAbcd.myX * myAbcd.myW;
		tempPoint.myY = myAbcd.myY * myAbcd.myW;
		tempPoint.myZ = myAbcd.myZ * myAbcd.myW;
		aPosition -= tempPoint;

		Vector3<Type> tempNormal;
		tempNormal.myX = myAbcd.myX;
		tempNormal.myY = myAbcd.myY;
		tempNormal.myZ = myAbcd.myZ;

		if (Dot(tempNormal, aPosition) > 0)
		{
			return false;
		}
		return true;
	}
	template<typename Type>
	bool Plane<Type>::Inside(Vector3<Type> aPosition) const
	{
		Vector3<Type> tempPoint;
		tempPoint.myX = myAbcd.myX * myAbcd.myW;
		tempPoint.myY = myAbcd.myY * myAbcd.myW;
		tempPoint.myZ = myAbcd.myZ * myAbcd.myW;
		aPosition -= tempPoint;

		Vector3<Type> tempNormal;
		tempNormal.myX = myAbcd.myX;
		tempNormal.myY = myAbcd.myY;
		tempNormal.myZ = myAbcd.myZ;

		if (Dot(tempNormal, aPosition) > 0)
		{
			return false;
		}
		return true;
	}
	template<typename Type>
	Vector3<Type> Plane<Type>::GetNormal() const
	{
		return myNormal;
	}
	template<typename Type>
	Vector4<Type> Plane<Type>::GetAbcd() const
	{
		return myAbcd;
	}
}
namespace CU = CommonUtilities;