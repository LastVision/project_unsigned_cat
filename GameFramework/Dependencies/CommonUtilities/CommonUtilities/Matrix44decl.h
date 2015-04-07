#pragma once
#include "Vector.h"
#include <cmath>
namespace CommonUtilities
{
	template<typename Type>
	class Matrix44
	{
	public:
		Type myMatrix[16];

		Matrix44();
		Matrix44(const Matrix44<Type> &aMatrix);
		~Matrix44();

		Matrix44<Type>& operator=(const Matrix44<Type> &aMatrix);

		void RotateX(float aRadian);
		void SetRotationX(float aRadian);

		void RotateY(float aRadian);
		void SetRotationY(float aRadian);

		void RotateZ(float aRadian);
		void SetRotationZ(float aRadian);

		static Matrix44<Type> CreateRotateAroundX(Type aAngleInRadians);
		static Matrix44<Type> CreateRotateAroundY(Type aAngleInRadians);
		static Matrix44<Type> CreateRotateAroundZ(Type aAngleInRadians);

		static Matrix44<Type> CreateProjectionMatrixLH(Type aNearZ, Type aFarZ, Type aAspectRatio, Type aFovAngle);

		static Matrix44<Type> Transpose(const Matrix44<Type> &aMatrixToTranspose);

		Vector4<Type> GetTranslation();
		void SetTranslation(Vector4<Type> aVector);
		Matrix44<Type> GetInverse() const;
	};
	template<typename Type>
	Matrix44<Type>::Matrix44()
	{
		for (int i = 0; i < 16; ++i)
		{
			if (i == 0 || i == 5 || i == 10 || i== 15)
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
	Matrix44<Type>::Matrix44(const Matrix44<Type> &aMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
	}
	template<typename Type>
	Matrix44<Type>::~Matrix44()
	{

	}
	template<typename Type>
	Matrix44<Type>& Matrix44<Type>::operator=(const Matrix44<Type> &aMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
		return *this;
	}
	template<typename Type>
	void Matrix44<Type>::RotateX(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundX(aRadian);
		Matrix44<Type> tempMatrix(*this);
		tempMatrix *= rotationMatrix;
		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}
	template<typename Type>
	void Matrix44<Type>::SetRotationX(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundX(aRadian);
		myMatrix[0] = rotationMatrix.myMatrix[0];
		myMatrix[1] = rotationMatrix.myMatrix[1];
		myMatrix[2] = rotationMatrix.myMatrix[2];
		myMatrix[4] = rotationMatrix.myMatrix[4];
		myMatrix[5] = rotationMatrix.myMatrix[5];
		myMatrix[6] = rotationMatrix.myMatrix[6];
		myMatrix[8] = rotationMatrix.myMatrix[8];
		myMatrix[9] = rotationMatrix.myMatrix[9];
		myMatrix[10] = rotationMatrix.myMatrix[10];
	}
	template<typename Type>
	void Matrix44<Type>::RotateY(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundY(aRadian);
		Matrix44<Type> tempMatrix(*this);
		tempMatrix *= rotationMatrix;
		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}
	template<typename Type>
	void Matrix44<Type>::SetRotationY(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundY(aRadian);
		myMatrix[0] = rotationMatrix.myMatrix[0];
		myMatrix[1] = rotationMatrix.myMatrix[1];
		myMatrix[2] = rotationMatrix.myMatrix[2];
		myMatrix[4] = rotationMatrix.myMatrix[4];
		myMatrix[5] = rotationMatrix.myMatrix[5];
		myMatrix[6] = rotationMatrix.myMatrix[6];
		myMatrix[8] = rotationMatrix.myMatrix[8];
		myMatrix[9] = rotationMatrix.myMatrix[9];
		myMatrix[10] = rotationMatrix.myMatrix[10];
	}
	template<typename Type>
	void Matrix44<Type>::RotateZ(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundZ(aRadian);
		Matrix44<Type> tempMatrix(*this);
		tempMatrix *= rotationMatrix;
		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}
	template<typename Type>
	void Matrix44<Type>::SetRotationZ(float aRadian)
	{
		Matrix44<Type> rotationMatrix = CreateRotateAroundZ(aRadian);
		myMatrix[0] = rotationMatrix.myMatrix[0];
		myMatrix[1] = rotationMatrix.myMatrix[1];
		myMatrix[2] = rotationMatrix.myMatrix[2];
		myMatrix[4] = rotationMatrix.myMatrix[4];
		myMatrix[5] = rotationMatrix.myMatrix[5];
		myMatrix[6] = rotationMatrix.myMatrix[6];
		myMatrix[8] = rotationMatrix.myMatrix[8];
		myMatrix[9] = rotationMatrix.myMatrix[9];
		myMatrix[10] = rotationMatrix.myMatrix[10];
	}
	template<typename Type>
	Matrix44<Type> Matrix44<Type>::CreateRotateAroundX(Type aAngleInRadians)
	{
		Matrix44<Type>rotateMatrix;
		for (int i = 0; i < 16; ++i)
		{
			if (i == 0 || i == 15)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 5 || i == 10)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 6)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else if (i == 9)
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
	Matrix44<Type> Matrix44<Type>::CreateRotateAroundY(Type aAngleInRadians)
	{
		Matrix44<Type>rotateMatrix;
		for (int i = 0; i < 9; ++i)
		{
			if (i == 5 || i == 15)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 0 || i == 10)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 2)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else if (i == 8)
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
	Matrix44<Type> Matrix44<Type>::CreateRotateAroundZ(Type aAngleInRadians)
	{
		Matrix44<Type>rotateMatrix;
		for (int i = 0; i < 9; ++i)
		{
			if (i == 10 || i == 15)
			{
				rotateMatrix.myMatrix[i] = 1;
			}
			else if (i == 0 || i == 5)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(cos(aAngleInRadians));
			}
			else if (i == 1)
			{
				rotateMatrix.myMatrix[i] = static_cast<Type>(sin(aAngleInRadians));
			}
			else if (i == 4)
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
	Matrix44<Type> Matrix44<Type>::CreateProjectionMatrixLH(Type aNearZ, Type aFarZ, Type aAspectRatio, Type aFovAngle)
	{
		Matrix44 temp;
		Type sinFov;
		Type cosFov;
		Type height;
		Type width;
		
		sinFov = sin(0.5f * aFovAngle);
		cosFov = cos(0.5f * aFovAngle);

		height = cosFov / sinFov;
		width = height / aAspectRatio;

		Type scaling = aFarZ / (aFarZ - aNearZ);
		
		temp.myMatrix[0] = width;
		temp.myMatrix[5] = height;
		temp.myMatrix[10] = scaling;
		temp.myMatrix[11] = 1;
		temp.myMatrix[14] = -scaling * aNearZ;
		temp.myMatrix[15] = 0;

		return temp;
	}
	template<typename Type>
	Matrix44<Type> Matrix44<Type>::Transpose(const Matrix44<Type> &aMatrixToTranspose)
	{
		Matrix44<Type> transposedMatrix;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				transposedMatrix.myMatrix[j + (i * 4)] = aMatrixToTranspose.myMatrix[i + (j * 4)];
			}
		}

		return transposedMatrix;
	}
	template<typename Type>
	Vector4<Type> Matrix44<Type>::GetTranslation()
	{
		Vector4<Type> toReturn;
		toReturn.x = myMatrix[12];
		toReturn.y = myMatrix[13];
		toReturn.z = myMatrix[14];
		toReturn.w = myMatrix[15];
		return toReturn;
	}
	template<typename Type>
	void Matrix44<Type>::SetTranslation(Vector4<Type> aVector)
	{
		myMatrix[12] = aVector.x;
		myMatrix[13] = aVector.y;
		myMatrix[14] = aVector.z;
		myMatrix[15] = aVector.w;
	}
	template<typename Type>
	Matrix44<Type> Matrix44<Type>::GetInverse() const
	{
		Matrix44<Type> invertedMatrix = *this;
		Vector4<Type> translation = invertedMatrix.GetTranslation();
		Vector4<Type> zeroTranslation;
		zeroTranslation.myX = 0;
		zeroTranslation.myY = 0;
		zeroTranslation.myZ = 0;
		zeroTranslation.myW = 1;
		invertedMatrix.SetTranslation(zeroTranslation);
		translation *= static_cast<Type>(-1);
		translation.myW = 1;
		invertedMatrix = Transpose(invertedMatrix);
		translation = translation * invertedMatrix;
		invertedMatrix.SetTranslation(translation);
		return invertedMatrix;
	}
} namespace CU = CommonUtilities;