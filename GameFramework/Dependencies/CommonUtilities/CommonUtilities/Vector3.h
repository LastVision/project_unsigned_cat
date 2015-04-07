#pragma once
#include "Vector3decl.h"
#include <math.h>

template <typename TYPE>
Vector3<TYPE> operator+(const Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX + aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY + aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ + aRightHandedVector.myZ;
	return tempVector;
}

template <typename TYPE>
Vector3<TYPE> operator-(const Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX - aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY - aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ - aRightHandedVector.myZ;
	return tempVector;
}

template <typename TYPE>
Vector3<TYPE> operator*(const Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ * aRightHandedVector.myZ;
	return tempVector;
}

template <typename TYPE>
Vector3<TYPE> operator/(const Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ / aRightHandedVector.myZ;
	return tempVector;
}

template <typename TYPE>
Vector3<TYPE> operator*(const Vector3<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedScalar;
	tempVector.myZ = aLeftHandedVector.myZ * aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
Vector3<TYPE> operator/(const Vector3<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedScalar;
	tempVector.myZ = aLeftHandedVector.myZ / aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
void operator+=(Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX += aRightHandedVector.myX;
	aLeftHandedVector.myY += aRightHandedVector.myY;
	aLeftHandedVector.myZ += aRightHandedVector.myZ;
}

template <typename TYPE>
void operator-=(Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX -= aRightHandedVector.myX;
	aLeftHandedVector.myY -= aRightHandedVector.myY;
	aLeftHandedVector.myZ -= aRightHandedVector.myZ;
}

template <typename TYPE>
void operator*=(Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX *= aRightHandedVector.myX;
	aLeftHandedVector.myY *= aRightHandedVector.myY;
	aLeftHandedVector.myZ *= aRightHandedVector.myZ;
}

template <typename TYPE>
void operator/=(Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX /= aRightHandedVector.myX;
	aLeftHandedVector.myY /= aRightHandedVector.myY;
	aLeftHandedVector.myZ /= aRightHandedVector.myZ;
}

template <typename TYPE>
void operator*=(Vector3<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX *= aRightHandedScalar;
	aLeftHandedVector.myY *= aRightHandedScalar;
	aLeftHandedVector.myZ *= aRightHandedScalar;
}

template <typename TYPE>
void operator/=(Vector3<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX /= aRightHandedScalar;
	aLeftHandedVector.myY /= aRightHandedScalar;
	aLeftHandedVector.myZ /= aRightHandedScalar;
}

template <typename TYPE>
bool operator==(const Vector3<TYPE> &aLeftHandedVector, const Vector3<TYPE> &aRightHandedVector)
{
	if (aLeftHandedVector.myX == aRightHandedVector.myX && aLeftHandedVector.myY == aRightHandedVector.myY && aLeftHandedVector.myZ == aRightHandedVector.myZ)
	{
		return true;
	}
	return false;
}


template <typename TYPE>
TYPE Length2(const Vector3<TYPE> &aVector)
{
	return ((aVector.myX * aVector.myX) + (aVector.myY * aVector.myY) + (aVector.myZ * aVector.myZ));
}

template <typename TYPE>
TYPE Length(const Vector3<TYPE> &aVector)
{
	return static_cast<TYPE>(sqrt(Length2(aVector)));
}

template <typename TYPE>
void Normalize(Vector3<TYPE> &aVector)
{
	aVector /= Length(aVector);
}

template <typename TYPE>
Vector3<TYPE> GetNormalized(Vector3<TYPE> &aVector)
{
	Vector3<TYPE> tempVector = aVector / Length(aVector);
	return tempVector;
}

template <typename TYPE>
TYPE Dot(const Vector3<TYPE> &aFirstVector, const Vector3<TYPE> &aSecondVector)
{
	return ((aFirstVector.myX * aSecondVector.myX) + (aFirstVector.myY * aSecondVector.myY) + (aFirstVector.myZ * aSecondVector.myZ));
}

template <typename TYPE>
Vector3<TYPE> Cross(const Vector3<TYPE> &aFirstVector, const Vector3<TYPE> &aSecondVector)
{
	Vector3<TYPE> tempVector;
	tempVector.myX = (aFirstVector.myY * aSecondVector.myZ) - (aFirstVector.myZ * aSecondVector.myY);
	tempVector.myY = (aFirstVector.myZ * aSecondVector.myX) - (aFirstVector.myX * aSecondVector.myZ);
	tempVector.myZ = (aFirstVector.myX * aSecondVector.myY) - (aFirstVector.myY * aSecondVector.myX);
	return tempVector;
}
//template class Vector3<int>;