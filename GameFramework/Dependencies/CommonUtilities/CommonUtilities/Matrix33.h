#pragma once
#include "Matrix33decl.h"
#include "Vector.h"

namespace CommonUtilities
{
	template <typename Type>
	Matrix33<Type> operator+(const Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		Matrix33<Type> tempMatrix;
		for (int i = 0; i < 9; ++i)
		{
			tempMatrix.myMatrix[i] = aLeftHandedMatrix.myMatrix[i] + aRightHandedMatrix.myMatrix[i];
		}
		return tempMatrix;
	}
	template <typename Type>
	void operator+=(Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			aLeftHandedMatrix.myMatrix[i] += aRightHandedMatrix.myMatrix[i];
		}
	}
	template <typename Type>
	Matrix33<Type> operator-(const Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		Matrix33<Type> tempMatrix;
		for (int i = 0; i < 9; ++i)
		{
			tempMatrix.myMatrix[i] = aLeftHandedMatrix.myMatrix[i] - aRightHandedMatrix.myMatrix[i];
		}
		return tempMatrix;
	}
	template <typename Type>
	void operator-=(Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			aLeftHandedMatrix.myMatrix[i] -= aRightHandedMatrix.myMatrix[i];
		}
	}
	template <typename Type>
	Matrix33<Type> operator*(const Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		Matrix33<Type> tempMatrix;
		Vector3<Type> rowVector1;
		Vector3<Type> rowVector2;
		Vector3<Type> rowVector3;
		Vector3<Type> colVector1;
		Vector3<Type> colVector2;
		Vector3<Type> colVector3;

		rowVector1.x = aLeftHandedMatrix.myMatrix[0];
		rowVector1.y = aLeftHandedMatrix.myMatrix[1];
		rowVector1.z = aLeftHandedMatrix.myMatrix[2];
		rowVector2.x = aLeftHandedMatrix.myMatrix[3];
		rowVector2.y = aLeftHandedMatrix.myMatrix[4];
		rowVector2.z = aLeftHandedMatrix.myMatrix[5];
		rowVector3.x = aLeftHandedMatrix.myMatrix[6];
		rowVector3.y = aLeftHandedMatrix.myMatrix[7];
		rowVector3.z = aLeftHandedMatrix.myMatrix[8];

		colVector1.x = aRightHandedMatrix.myMatrix[0];
		colVector1.y = aRightHandedMatrix.myMatrix[3];
		colVector1.z = aRightHandedMatrix.myMatrix[6];
		colVector2.x = aRightHandedMatrix.myMatrix[1];
		colVector2.y = aRightHandedMatrix.myMatrix[4];
		colVector2.z = aRightHandedMatrix.myMatrix[7];
		colVector3.x = aRightHandedMatrix.myMatrix[2];
		colVector3.y = aRightHandedMatrix.myMatrix[5];
		colVector3.z = aRightHandedMatrix.myMatrix[8];

		tempMatrix.myMatrix[0] = Dot(rowVector1, colVector1);
		tempMatrix.myMatrix[1] = Dot(rowVector1, colVector2);
		tempMatrix.myMatrix[2] = Dot(rowVector1, colVector3);
		tempMatrix.myMatrix[3] = Dot(rowVector2, colVector1);
		tempMatrix.myMatrix[4] = Dot(rowVector2, colVector2);
		tempMatrix.myMatrix[5] = Dot(rowVector2, colVector3);
		tempMatrix.myMatrix[6] = Dot(rowVector3, colVector1);
		tempMatrix.myMatrix[7] = Dot(rowVector3, colVector2);
		tempMatrix.myMatrix[8] = Dot(rowVector3, colVector3);

		return tempMatrix;
	}
	template <typename Type>
	void operator*=(Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		Vector3<Type> rowVector1;
		Vector3<Type> rowVector2;
		Vector3<Type> rowVector3;
		Vector3<Type> colVector1;
		Vector3<Type> colVector2;
		Vector3<Type> colVector3;

		rowVector1.x = aLeftHandedMatrix.myMatrix[0];
		rowVector1.y = aLeftHandedMatrix.myMatrix[1];
		rowVector1.z = aLeftHandedMatrix.myMatrix[2];
		rowVector2.x = aLeftHandedMatrix.myMatrix[3];
		rowVector2.y = aLeftHandedMatrix.myMatrix[4];
		rowVector2.z = aLeftHandedMatrix.myMatrix[5];
		rowVector3.x = aLeftHandedMatrix.myMatrix[6];
		rowVector3.y = aLeftHandedMatrix.myMatrix[7];
		rowVector3.z = aLeftHandedMatrix.myMatrix[8];

		colVector1.x = aRightHandedMatrix.myMatrix[0];
		colVector1.y = aRightHandedMatrix.myMatrix[3];
		colVector1.z = aRightHandedMatrix.myMatrix[6];
		colVector2.x = aRightHandedMatrix.myMatrix[1];
		colVector2.y = aRightHandedMatrix.myMatrix[4];
		colVector2.z = aRightHandedMatrix.myMatrix[7];
		colVector3.x = aRightHandedMatrix.myMatrix[2];
		colVector3.y = aRightHandedMatrix.myMatrix[5];
		colVector3.z = aRightHandedMatrix.myMatrix[8];

		aLeftHandedMatrix.myMatrix[0] = Dot(rowVector1, colVector1);
		aLeftHandedMatrix.myMatrix[1] = Dot(rowVector1, colVector2);
		aLeftHandedMatrix.myMatrix[2] = Dot(rowVector1, colVector3);
		aLeftHandedMatrix.myMatrix[3] = Dot(rowVector2, colVector1);
		aLeftHandedMatrix.myMatrix[4] = Dot(rowVector2, colVector2);
		aLeftHandedMatrix.myMatrix[5] = Dot(rowVector2, colVector3);
		aLeftHandedMatrix.myMatrix[6] = Dot(rowVector3, colVector1);
		aLeftHandedMatrix.myMatrix[7] = Dot(rowVector3, colVector2);
		aLeftHandedMatrix.myMatrix[8] = Dot(rowVector3, colVector3);
	}
	template <typename Type>
	Vector3<Type> operator*(const Vector3<Type> &aLeftHandedVector, const Matrix33<Type> &aRightHandedMatrix)
	{
		Vector3<Type> tempVector;
		for (int i = 0; i < 3; ++i)
		{
			Vector3<Type> colVector;
			colVector.x = aRightHandedMatrix.myMatrix[i];
			colVector.y = aRightHandedMatrix.myMatrix[i + 3];
			colVector.z = aRightHandedMatrix.myMatrix[i + 6];
			if (i == 0)
			{
				tempVector.myX = Dot(aLeftHandedVector, colVector);
			}
			else if (i == 1)
			{
				tempVector.myY = Dot(aLeftHandedVector, colVector);
			}
			else if (i == 2)
			{
				tempVector.myZ = Dot(aLeftHandedVector, colVector);
			}
		}
		return tempVector;
	}
	template <typename Type>
	Vector2<Type> operator*(const Vector2<Type> &aLeftHandedVector, const Matrix33<Type> &aRightHandedMatrix)
	{
		Vector2<Type> vectorToReturn;
		Vector3<Type> tempVector3;
		
		tempVector3.myX = aLeftHandedVector.myX;
		tempVector3.myY = aLeftHandedVector.myY;
		tempVector3.myZ = 1;

		for (int i = 0; i < 2; ++i)
		{
			Vector3<Type> colVector;
			colVector.x = aRightHandedMatrix.myMatrix[i];
			colVector.y = aRightHandedMatrix.myMatrix[i + 3];
			colVector.z = aRightHandedMatrix.myMatrix[i + 6];
			if (i == 0)
			{
				vectorToReturn.myX = Dot(tempVector3, colVector);
			}
			else if (i == 1)
			{
				vectorToReturn.myY = Dot(tempVector3, colVector);
			}
		}
		return vectorToReturn;
	}
	template <typename Type>
	bool operator==(const Matrix33<Type> &aLeftHandedMatrix, const Matrix33<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (aLeftHandedMatrix.myMatrix[i] != aRightHandedMatrix.myMatrix[i])
			{
				return false;
			}
		}
		return true;
	}
} 
namespace CU = CommonUtilities;

template class CU::Matrix33 < float > ;