#pragma once
#include "Vector2decl.h"
#include <math.h>

template <typename TYPE>
Vector2<TYPE> operator+(const Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX + aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY + aRightHandedVector.myY;
	return tempVector;
}

template <typename TYPE>
Vector2<TYPE> operator-(const Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX - aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY - aRightHandedVector.myY;
	return tempVector;
}

template <typename TYPE>
Vector2<TYPE> operator*(const Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedVector.myY;
	return tempVector;
}

template <typename TYPE>
Vector2<TYPE> operator/(const Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedVector.myY;
	return tempVector;
}

template <typename TYPE>
Vector2<TYPE> operator*(const Vector2<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
Vector2<TYPE> operator/(const Vector2<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector2<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
void operator+=(Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX += aRightHandedVector.myX;
	aLeftHandedVector.myY += aRightHandedVector.myY;
}

template <typename TYPE>
void operator-=(Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX -= aRightHandedVector.myX;
	aLeftHandedVector.myY -= aRightHandedVector.myY;
}

template <typename TYPE>
void operator*=(Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX *= aRightHandedVector.myX;
	aLeftHandedVector.myY *= aRightHandedVector.myY;
}

template <typename TYPE>
void operator/=(Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX /= aRightHandedVector.myX;
	aLeftHandedVector.myY /= aRightHandedVector.myY;
}

template <typename TYPE>
void operator*=(Vector2<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX *= aRightHandedScalar;
	aLeftHandedVector.myY *= aRightHandedScalar;
}

template <typename TYPE>
void operator/=(Vector2<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX /= aRightHandedScalar;
	aLeftHandedVector.myY /= aRightHandedScalar;
}

template <typename TYPE>
bool operator==(const Vector2<TYPE> &aLeftHandedVector, const Vector2<TYPE> &aRightHandedVector)
{
	if (aLeftHandedVector.myX == aRightHandedVector.myX && aLeftHandedVector.myY == aRightHandedVector.myY)
	{
		return true;
	}
	return false;
}

template <typename TYPE>
TYPE Length2(const Vector2<TYPE> &aVector)
{
	return ((aVector.myX * aVector.myX) + (aVector.myY * aVector.myY));
}

template <typename TYPE>
TYPE Length(const Vector2<TYPE> &aVector)
{
	return static_cast<TYPE>(sqrt(Length2(aVector)));
}

template <typename TYPE>
void Normalize(Vector2<TYPE> &aVector)
{
	aVector /= Length(aVector);
}

template <typename TYPE>
Vector2<TYPE> GetNormalized(const Vector2<TYPE> &aVector)
{
	Vector2<TYPE> tempVector = aVector / Length(aVector);
	return tempVector;
}

template <typename TYPE>
TYPE Dot(const Vector2<TYPE> &aFirstVector, const Vector2<TYPE> &aSecondVector)
{
	return ((aFirstVector.myX * aSecondVector.myX) + (aFirstVector.myY * aSecondVector.myY));
}