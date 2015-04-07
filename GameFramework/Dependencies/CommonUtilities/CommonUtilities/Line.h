#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	template<typename Type>
	class Line
	{
	public:
		Line();
		Line(Vector2<Type> aFirstPoint, Vector2<Type>aSecondPoint);
		~Line();
		bool operator==(const Line<Type> &aLine);
		void InitWith2Pointers(Vector2<Type> aFirstPoint, Vector2<Type> aSecondPoint);
		void InitWithPointAndDirection(Vector2<Type> aPoint, Vector2<Type> aDirection);
		bool Inside(Vector2<Type> aPosition);
		Vector3<Type> GetAbc() const;
	private:
		Vector3<Type> myAbc;
	};

	template<typename Type>
	Line<Type>::Line()
	{
		myAbc.myX = 0;
		myAbc.myY = 0;
		myAbc.myZ = 0;
	}
	template<typename Type>
	Line<Type>::Line(Vector2<Type> aFirstPoint, Vector2<Type>aSecondPoint)
	{
		aFirstPoint -= aSecondPoint;
		Normalize(aFirstPoint);

		Type oldX = aFirstPoint.myX;

		aFirstPoint.myX = -aFirstPoint.myY;
		aFirstPoint.myY = oldX;

		myAbc.myX = aFirstPoint.myX;
		myAbc.myY = aFirstPoint.myY;
		myAbc.myZ = Dot(aFirstPoint, aSecondPoint);
	}
	template<typename Type>
	Line<Type>::~Line()
	{

	}
	template<typename Type>
	bool Line<Type>::operator==(const Line<Type> &aLine)
	{
		if (myAbc == aLine.myAbc)
		{
			return true;
		}
		return false;
	}
	template<typename Type>
	void Line<Type>::InitWith2Pointers(Vector2<Type> aFirstPoint, Vector2<Type> aSecondPoint)
	{
		aFirstPoint -= aSecondPoint;
		
		Normalize(aFirstPoint);

		Type oldX = aFirstPoint.myX;

		aFirstPoint.myX = -aFirstPoint.myY;
		aFirstPoint.myY = oldX;

		myAbc.myX = aFirstPoint.myX;
		myAbc.myY = aFirstPoint.myY;
		myAbc.myZ = Dot(aFirstPoint, aSecondPoint);
	}
	template<typename Type>
	void Line<Type>::InitWithPointAndDirection(Vector2<Type> aPoint, Vector2<Type> aDirection)
	{
		Normalize(aDirection);

		Type oldX = aDirection.myX;

		aDirection.myX = -aDirection.myY;
		aDirection.myY = oldX;

		myAbc.myX = aDirection.myX;
		myAbc.myY = aDirection.myY;
		myAbc.myZ = Dot(aDirection, aPoint);
	}
	template<typename Type>
	bool Line<Type>::Inside(Vector2<Type> aPosition)
	{
		Vector2<Type> tempPoint;
		tempPoint.myX = myAbc.myX * myAbc.myZ;
		tempPoint.myY = myAbc.myY * myAbc.myZ;
		aPosition -= tempPoint;

		Vector2<Type> tempNormal;
		tempNormal.myX = myAbc.myX;
		tempNormal.myY = myAbc.myY;

		if (Dot(tempNormal, aPosition) > 0)
		{
			return false;
		}
		return true;
	}
	template<typename Type>
	Vector3<Type> Line<Type>::GetAbc() const
	{
		return myAbc;
	}
}
namespace CU = CommonUtilities;