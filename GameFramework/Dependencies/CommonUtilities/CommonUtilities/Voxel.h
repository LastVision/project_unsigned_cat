#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	struct Voxel
	{
		inline Voxel();
		inline Voxel(Vector3<float> aPosition, Vector3<float> aColor, Vector3<float> aNormal);
		Vector3<float> myPosition;
		Vector3<float> myColor;
		Vector3<float> myNormal;
	};

	Voxel::Voxel()
	{

	}

	Voxel::Voxel(Vector3<float> aPosition, Vector3<float> aColor, Vector3<float> aNormal)
	{
		myPosition = aPosition;
		myColor = aColor;
		myNormal = aNormal;
	}

} namespace CU = CommonUtilities;


