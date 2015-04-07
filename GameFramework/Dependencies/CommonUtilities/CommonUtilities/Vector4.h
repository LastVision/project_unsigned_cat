#pragma once
#include "Vector4decl.h"
#include <math.h>

template <typename TYPE>
Vector4<TYPE> operator+(const Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX + aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY + aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ + aRightHandedVector.myZ;
	tempVector.myW = aLeftHandedVector.myW + aRightHandedVector.myW;
	return tempVector;
}

template <typename TYPE>
Vector4<TYPE> operator-(const Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX - aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY - aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ - aRightHandedVector.myZ;
	tempVector.myW = aLeftHandedVector.myW - aRightHandedVector.myW;
	return tempVector;
}

template <typename TYPE>
Vector4<TYPE> operator*(const Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ * aRightHandedVector.myZ;
	tempVector.myW = aLeftHandedVector.myW * aRightHandedVector.myW;
	return tempVector;
}

template <typename TYPE>
Vector4<TYPE> operator/(const Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedVector.myX;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedVector.myY;
	tempVector.myZ = aLeftHandedVector.myZ / aRightHandedVector.myZ;
	tempVector.myW = aLeftHandedVector.myW / aRightHandedVector.myW;
	return tempVector;
}

template <typename TYPE>
Vector4<TYPE> operator*(const Vector4<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX * aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY * aRightHandedScalar;
	tempVector.myZ = aLeftHandedVector.myZ * aRightHandedScalar;
	tempVector.myW = aLeftHandedVector.myW * aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
Vector4<TYPE> operator/(const Vector4<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	Vector4<TYPE> tempVector;
	tempVector.myX = aLeftHandedVector.myX / aRightHandedScalar;
	tempVector.myY = aLeftHandedVector.myY / aRightHandedScalar;
	tempVector.myZ = aLeftHandedVector.myZ / aRightHandedScalar;
	tempVector.myW = aLeftHandedVector.myW / aRightHandedScalar;
	return tempVector;
}

template <typename TYPE>
void operator+=(Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX += aRightHandedVector.myX;
	aLeftHandedVector.myY += aRightHandedVector.myY;
	aLeftHandedVector.myZ += aRightHandedVector.myZ;
	aLeftHandedVector.myW += aRightHandedVector.myW;
}

template <typename TYPE>
void operator-=(Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX -= aRightHandedVector.myX;
	aLeftHandedVector.myY -= aRightHandedVector.myY;
	aLeftHandedVector.myZ -= aRightHandedVector.myZ;
	aLeftHandedVector.myW -= aRightHandedVector.myW;
}

template <typename TYPE>
void operator*=(Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX *= aRightHandedVector.myX;
	aLeftHandedVector.myY *= aRightHandedVector.myY;
	aLeftHandedVector.myZ *= aRightHandedVector.myZ;
	aLeftHandedVector.myW *= aRightHandedVector.myW;
}

template <typename TYPE>
void operator/=(Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	aLeftHandedVector.myX /= aRightHandedVector.myX;
	aLeftHandedVector.myY /= aRightHandedVector.myY;
	aLeftHandedVector.myZ /= aRightHandedVector.myZ;
	aLeftHandedVector.myW /= aRightHandedVector.myW;
}

template <typename TYPE>
void operator*=(Vector4<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX *= aRightHandedScalar;
	aLeftHandedVector.myY *= aRightHandedScalar;
	aLeftHandedVector.myZ *= aRightHandedScalar;
	aLeftHandedVector.myW *= aRightHandedScalar;
}

template <typename TYPE>
void operator/=(Vector4<TYPE> &aLeftHandedVector, const TYPE &aRightHandedScalar)
{
	aLeftHandedVector.myX /= aRightHandedScalar;
	aLeftHandedVector.myY /= aRightHandedScalar;
	aLeftHandedVector.myZ /= aRightHandedScalar;
	aLeftHandedVector.myW /= aRightHandedScalar;
}

template <typename TYPE>
bool operator==(const Vector4<TYPE> &aLeftHandedVector, const Vector4<TYPE> &aRightHandedVector)
{
	if (aLeftHandedVector.myX == aRightHandedVector.myX &&
		aLeftHandedVector.myY == aRightHandedVector.myY &&
		aLeftHandedVector.myZ == aRightHandedVector.myZ &&
		aLeftHandedVector.myW == aRightHandedVector.myW)
	{
		return true;
	}
	else
	{
		return false;
	}

}

template <typename TYPE>
TYPE Length2(const Vector4<TYPE> &aVector)
{
	return ((aVector.myX * aVector.myX) + (aVector.myY * aVector.myY) + (aVector.myZ * aVector.myZ) + (aVector.myW * aVector.myW));
}

template <typename TYPE>
TYPE Length(const Vector4<TYPE> &aVector)
{
	return static_cast<TYPE>(sqrt(Length2(aVector)));
}

template <typename TYPE>
void Normalize(Vector4<TYPE> &aVector)
{
	aVector /= Length(aVector);
}

template <typename TYPE>
Vector4<TYPE> GetNormalized(Vector4<TYPE> &aVector)
{
	Vector4<TYPE> tempVector = aVector / Length(aVector);
	return tempVector;
}

template <typename TYPE>
TYPE Dot(const Vector4<TYPE> &aFirstVector, const Vector4<TYPE> &aSecondVector)
{
	return ((aFirstVector.myX * aSecondVector.myX) + (aFirstVector.myY * aSecondVector.myY) + (aFirstVector.myZ * aSecondVector.myZ) + (aFirstVector.myW * aSecondVector.myW));
}