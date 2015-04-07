#pragma once
#include "Matrix44decl.h"
#include "Vector.h"

namespace CommonUtilities
{
	template <typename Type>
	Matrix44<Type> operator+(const Matrix44<Type> &aLeftHandedMatrix, const Matrix44<Type> &aRightHandedMatrix)
	{
		Matrix44<Type> tempMatrix;
		for (int i = 0; i < 16; ++i)
		{
			tempMatrix.myMatrix[i] = aLeftHandedMatrix.myMatrix[i] + aRightHandedMatrix.myMatrix[i];
		}
		return tempMatrix;
	}
	template <typename Type>
	void operator+=(Matrix44<Type> &aLeftHandedMatrix, const Matrix44<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			aLeftHandedMatrix.myMatrix[i] += aRightHandedMatrix.myMatrix[i];
		}
	}
	template <typename Type>
	Matrix44<Type> operator-(const Matrix44<Type> &aLeftHandedMatrix, const Matrix44<Type> &aRightHandedMatrix)
	{
		Matrix44<Type> tempMatrix;
		for (int i = 0; i < 16; ++i)
		{
			tempMatrix.myMatrix[i] = aLeftHandedMatrix.myMatrix[i] - aRightHandedMatrix.myMatrix[i];
		}
		return tempMatrix;
	}
	template <typename Type>
	void operator-=(Matrix44<Type> &aLeftHandedMatrix, const Matrix44<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			aLeftHandedMatrix.myMatrix[i] -= aRightHandedMatrix.myMatrix[i];
		}
	}
	template <typename type>
	Matrix44<type> operator*(const Matrix44<type> &aLeftHandMatrix, const Matrix44<type> &aRightHandMatrix)
	{
		Matrix44<type> tempMatrix;
		Vector4<type> rowVector1;
		Vector4<type> rowVector2;
		Vector4<type> rowVector3;
		Vector4<type> rowVector4;
		Vector4<type> colVector1;
		Vector4<type> colVector2;
		Vector4<type> colVector3;
		Vector4<type> colVector4;

		rowVector1.x = aLeftHandMatrix.myMatrix[0];
		rowVector1.y = aLeftHandMatrix.myMatrix[1];
		rowVector1.z = aLeftHandMatrix.myMatrix[2];
		rowVector1.w = aLeftHandMatrix.myMatrix[3];
		rowVector2.x = aLeftHandMatrix.myMatrix[4];
		rowVector2.y = aLeftHandMatrix.myMatrix[5];
		rowVector2.z = aLeftHandMatrix.myMatrix[6];
		rowVector2.w = aLeftHandMatrix.myMatrix[7];
		rowVector3.x = aLeftHandMatrix.myMatrix[8];
		rowVector3.y = aLeftHandMatrix.myMatrix[9];
		rowVector3.z = aLeftHandMatrix.myMatrix[10];
		rowVector3.w = aLeftHandMatrix.myMatrix[11];
		rowVector4.x = aLeftHandMatrix.myMatrix[12];
		rowVector4.y = aLeftHandMatrix.myMatrix[13];
		rowVector4.z = aLeftHandMatrix.myMatrix[14];
		rowVector4.w = aLeftHandMatrix.myMatrix[15];

		colVector1.x = aRightHandMatrix.myMatrix[0];
		colVector1.y = aRightHandMatrix.myMatrix[4];
		colVector1.z = aRightHandMatrix.myMatrix[8];
		colVector1.w = aRightHandMatrix.myMatrix[12];
		colVector2.x = aRightHandMatrix.myMatrix[1];
		colVector2.y = aRightHandMatrix.myMatrix[5];
		colVector2.z = aRightHandMatrix.myMatrix[9];
		colVector2.w = aRightHandMatrix.myMatrix[13];
		colVector3.x = aRightHandMatrix.myMatrix[2];
		colVector3.y = aRightHandMatrix.myMatrix[6];
		colVector3.z = aRightHandMatrix.myMatrix[10];
		colVector3.w = aRightHandMatrix.myMatrix[14];
		colVector4.x = aRightHandMatrix.myMatrix[3];
		colVector4.y = aRightHandMatrix.myMatrix[7];
		colVector4.z = aRightHandMatrix.myMatrix[11];
		colVector4.w = aRightHandMatrix.myMatrix[15];

		tempMatrix.myMatrix[0] = Dot(rowVector1, colVector1);
		tempMatrix.myMatrix[1] = Dot(rowVector1, colVector2);
		tempMatrix.myMatrix[2] = Dot(rowVector1, colVector3);
		tempMatrix.myMatrix[3] = Dot(rowVector1, colVector4);
		tempMatrix.myMatrix[4] = Dot(rowVector2, colVector1);
		tempMatrix.myMatrix[5] = Dot(rowVector2, colVector2);
		tempMatrix.myMatrix[6] = Dot(rowVector2, colVector3);
		tempMatrix.myMatrix[7] = Dot(rowVector2, colVector4);
		tempMatrix.myMatrix[8] = Dot(rowVector3, colVector1);
		tempMatrix.myMatrix[9] = Dot(rowVector3, colVector2);
		tempMatrix.myMatrix[10] = Dot(rowVector3, colVector3);
		tempMatrix.myMatrix[11] = Dot(rowVector3, colVector4);
		tempMatrix.myMatrix[12] = Dot(rowVector4, colVector1);
		tempMatrix.myMatrix[13] = Dot(rowVector4, colVector2);
		tempMatrix.myMatrix[14] = Dot(rowVector4, colVector3);
		tempMatrix.myMatrix[15] = Dot(rowVector4, colVector4);
		return tempMatrix;
	}
	template <typename type>
	void operator*=(Matrix44<type> &aLeftHandMatrix, const Matrix44<type> &aRightHandMatrix)
	{
		Vector4<type> rowVector1;
		Vector4<type> rowVector2;
		Vector4<type> rowVector3;
		Vector4<type> rowVector4;
		Vector4<type> colVector1;
		Vector4<type> colVector2;
		Vector4<type> colVector3;
		Vector4<type> colVector4;

		rowVector1.x = aLeftHandMatrix.myMatrix[0];
		rowVector1.y = aLeftHandMatrix.myMatrix[1];
		rowVector1.z = aLeftHandMatrix.myMatrix[2];
		rowVector1.w = aLeftHandMatrix.myMatrix[3];
		rowVector2.x = aLeftHandMatrix.myMatrix[4];
		rowVector2.y = aLeftHandMatrix.myMatrix[5];
		rowVector2.z = aLeftHandMatrix.myMatrix[6];
		rowVector2.w = aLeftHandMatrix.myMatrix[7];
		rowVector3.x = aLeftHandMatrix.myMatrix[8];
		rowVector3.y = aLeftHandMatrix.myMatrix[9];
		rowVector3.z = aLeftHandMatrix.myMatrix[10];
		rowVector3.w = aLeftHandMatrix.myMatrix[11];
		rowVector4.x = aLeftHandMatrix.myMatrix[12];
		rowVector4.y = aLeftHandMatrix.myMatrix[13];
		rowVector4.z = aLeftHandMatrix.myMatrix[14];
		rowVector4.w = aLeftHandMatrix.myMatrix[15];

		colVector1.x = aRightHandMatrix.myMatrix[0];
		colVector1.y = aRightHandMatrix.myMatrix[4];
		colVector1.z = aRightHandMatrix.myMatrix[8];
		colVector1.w = aRightHandMatrix.myMatrix[12];
		colVector2.x = aRightHandMatrix.myMatrix[1];
		colVector2.y = aRightHandMatrix.myMatrix[5];
		colVector2.z = aRightHandMatrix.myMatrix[9];
		colVector2.w = aRightHandMatrix.myMatrix[13];
		colVector3.x = aRightHandMatrix.myMatrix[2];
		colVector3.y = aRightHandMatrix.myMatrix[6];
		colVector3.z = aRightHandMatrix.myMatrix[10];
		colVector3.w = aRightHandMatrix.myMatrix[14];
		colVector4.x = aRightHandMatrix.myMatrix[3];
		colVector4.y = aRightHandMatrix.myMatrix[7];
		colVector4.z = aRightHandMatrix.myMatrix[11];
		colVector4.w = aRightHandMatrix.myMatrix[15];

		aLeftHandMatrix.myMatrix[0] = Dot(rowVector1, colVector1);
		aLeftHandMatrix.myMatrix[1] = Dot(rowVector1, colVector2);
		aLeftHandMatrix.myMatrix[2] = Dot(rowVector1, colVector3);
		aLeftHandMatrix.myMatrix[3] = Dot(rowVector1, colVector4);
		aLeftHandMatrix.myMatrix[4] = Dot(rowVector2, colVector1);
		aLeftHandMatrix.myMatrix[5] = Dot(rowVector2, colVector2);
		aLeftHandMatrix.myMatrix[6] = Dot(rowVector2, colVector3);
		aLeftHandMatrix.myMatrix[7] = Dot(rowVector2, colVector4);
		aLeftHandMatrix.myMatrix[8] = Dot(rowVector3, colVector1);
		aLeftHandMatrix.myMatrix[9] = Dot(rowVector3, colVector2);
		aLeftHandMatrix.myMatrix[10] = Dot(rowVector3, colVector3);
		aLeftHandMatrix.myMatrix[11] = Dot(rowVector3, colVector4);
		aLeftHandMatrix.myMatrix[12] = Dot(rowVector4, colVector1);
		aLeftHandMatrix.myMatrix[13] = Dot(rowVector4, colVector2);
		aLeftHandMatrix.myMatrix[14] = Dot(rowVector4, colVector3);
		aLeftHandMatrix.myMatrix[15] = Dot(rowVector4, colVector4);

	}
	template <typename Type>
	Vector4<Type> operator*(const Vector4<Type> &aLeftHandedVector, const Matrix44<Type> &aRightHandedMatrix)
	{
		Vector4<Type> tempVector;
		for (int i = 0; i < 4; ++i)
		{
			Vector4<Type> colVector;
			colVector.x = aRightHandedMatrix.myMatrix[i];
			colVector.y = aRightHandedMatrix.myMatrix[i + 4];
			colVector.z = aRightHandedMatrix.myMatrix[i + 8];
			colVector.w = aRightHandedMatrix.myMatrix[i + 12];
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
			else if (i == 3)
			{
				tempVector.myW = Dot(aLeftHandedVector, colVector);
			}
		}
		return tempVector;
	}
	template <typename Type>
	bool operator==(const Matrix44<Type> &aLeftHandedMatrix, const Matrix44<Type> &aRightHandedMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (aLeftHandedMatrix.myMatrix[i] != aRightHandedMatrix.myMatrix[i])
			{
				return false;
			}
		}
		return true;
	}
} namespace CU = CommonUtilities;