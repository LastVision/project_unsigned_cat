#pragma once
#include "Matrix44decl.h"
#include "Vector.h"
#include <math.h>

namespace CommonUtilities
{
	template<typename Type>
	class Matrix33
	{
	public:
		Type myMatrix[9];

		Matrix33();
		Matrix33(const Matrix33<Type> &aMatrix);
		Matrix33(Matrix44<Type> &aMatrix);
		~Matrix33();

		Matrix33<Type>& operator=(const Matrix33<Type> &aMatrix);

		void Rotate2D(float aRadian);
		void SetRotation2d(float aRadian);

		static Matrix33<Type> CreateRotateAroundX(Type aAngleInRadians);
		static Matrix33<Type> CreateRotateAroundY(Type aAngleInRadians);
		static Matrix33<Type> CreateRotateAroundZ(Type aAngleInRadians);

		static Matrix33<Type> Transpose(const Matrix33<Type> &aMatrixToTranspose);

		Vector3<Type> GetTranslation();
		void SetTranslation(Vector3<Type> aVector);
		Matrix33<Type> GetInverse();
	};
	template<typename Type>
	Matrix33<Type>::Matrix33()
	{
		for (int i = 0; i < 9; ++i)
		{
			if (i == 0 || i == 4 || i == 8)
			{
				myMatrix[i] = 1;
			}
			else
			{
				myMatrix[i] = 0;
			}
		}
	}
	template<typename Type>
	Matrix33<Type>::Matrix33(const Matrix33<Type> &aMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
	}
	template<typename Type>
	Matrix33<Type>::Matrix33(Matrix44<Type> &aMatrix)
	{
		int dataCounter = 0;
		for (int i = 0; i < 11; ++i)
		{
			if (i != 3 || i != 7)
			{
				myMatrix[dataCounter] = aMatrix.myMatrix[i];
				++dataCounter;
			}
		}
	}
	template<typename Type>
	Matrix33<Type>::~Matrix33()
	{

	}
	template<typename Type>
	Matrix33<Type>& Matrix33<Type>::operator=(const Matrix33<Type> &aMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
		return *this;
	}
	template<typename Type>
	void Matrix33<Type>::Rotate2D(float aRadian)
	{
		Matrix33<Type> rotationMatrix = CreateRotateAroundZ(aRadian);
		Matrix33<Type> tempMatrix(*this);
		tempMatrix *= rotationMatrix;
		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[3] = tempMatrix.myMatrix[3];
		myMatrix[4] = tempMatrix.myMatrix[4];
	}
	template<typename Type>
	void Matrix33<Type>::SetRotation2d(float aRadian)
	{
		Matrix33<Type> rotationMatrix = CreateRotateAroundZ(aRadian);
		myMatrix[0] = rotationMatrix.myMatrix[0];
		myMatrix[1] = rotationMatrix.myMatrix[1];
		myMatrix[3] = rotationMatrix.myMatrix[3];
		myMatrix[4] = rotationMatrix.myMatrix[4];
	}
	template<typename Type>
	Matrix33<Type> Matrix33<Type>::CreateRotateAroundX(Type aAngleInRadians)
	{
		Matrix33<Type>rotateMatrix;
		for (int i = 0; i < 9; ++i)
		{
			if (i == 0)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 4 || i == 8)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 5)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else if (i == 7)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(-sin(aAngleInRadians));
			}
			else
			{
				rotateMatrix.myMatrix[i] = 0;
			}
		}
		return rotateMatrix;
	}
	template<typename Type>
	Matrix33<Type> Matrix33<Type>::CreateRotateAroundY(Type aAngleInRadians)
	{
		Matrix33<Type>rotateMatrix;
		for (int i = 0; i < 9; ++i)
		{
			if (i == 4)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 0 || i == 8)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 2)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(-sin(aAngleInRadians));
			}
			else if (i == 6)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else
			{
				rotateMatrix.myMatrix[i] = 0;
			}
		}
		return rotateMatrix;
	}
	template<typename Type>
	Matrix33<Type> Matrix33<Type>::CreateRotateAroundZ(Type aAngleInRadians)
	{
		Matrix33<Type>rotateMatrix;
		for (int i = 0; i < 9; ++i)
		{
			if (i == 8)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 0 || i == 4)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 1)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else if (i == 3)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(-sin(aAngleInRadians));
			}
			else
			{
				rotateMatrix.myMatrix[i] = 0;
			}
		}
		return rotateMatrix;
	}
	template<typename Type>
	Matrix33<Type> Matrix33<Type>::Transpose(const Matrix33<Type> &aMatrixToTranspose)
	{
		Matrix33<Type> transposedMatrix;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				transposedMatrix.myMatrix[j + (i * 3)] = aMatrixToTranspose.myMatrix[i + (j * 3)];
			}
		}

		return transposedMatrix;
	}
	template<typename Type>
	Vector3<Type> Matrix33<Type>::GetTranslation()
	{
		Vector3<Type> toReturn;
		toReturn.x = myMatrix[6];
		toReturn.y = myMatrix[7];
		toReturn.z = myMatrix[8];
		return toReturn;
	}
	template<typename Type>
	void Matrix33<Type>::SetTranslation(Vector3<Type> aVector)
	{
		myMatrix[6] = aVector.x;
		myMatrix[7] = aVector.y;
		myMatrix[8] = aVector.z;
	}
	template<typename Type>
	Matrix33<Type> Matrix33<Type>::GetInverse()
	{
		Matrix33<Type> invertedMatrix = *this;
		Vector3<Type> translation = invertedMatrix.GetTranslation();
		Vector3<Type> zeroTranslation;
		zeroTranslation.myX = 0;
		zeroTranslation.myY = 0;
		zeroTranslation.myZ = 1;
		invertedMatrix.SetTranslation(zeroTranslation);
		translation *= static_cast<Type>(-1);
		translation.myZ = 1;
		invertedMatrix = Transpose(invertedMatrix);
		translation = translation * invertedMatrix;
		invertedMatrix.SetTranslation(translation);
		return invertedMatrix;
	}
} namespace CU = CommonUtilities;