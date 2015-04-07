#pragma once
#include "Vector.h"
#include "Voxel.h"
namespace CommonUtilities
{
	class BaseLight
	{
	public:
		virtual ~BaseLight();
		virtual Vector3<float> GetColor(Voxel aVoxel, Vector3<float> aCameraNormal);
	protected:
		BaseLight();

		virtual Vector3<float> Diffuse(Vector3<float> aNormal, Vector3<float> aLightDirection, Vector3<float> aVoxelColor, Vector3<float> aLightColor);
		virtual Vector3<float> Specular(Vector3<float> aHalfAngle, Vector3<float> aNormal, float aSpecularPower, Vector3<float> aLightColor);
		
		float Saturate(float aDotProduct);
		Vector3<float> GetHalfAngle(Vector3<float> aCameraNormal, Vector3<float> aLightDirection);
	protected:
		Vector3<float> myLightColor;
		Vector3<float> myLightDirection;
		float mySpecularPower;
	private:
		Vector3<float> myDiffuse;
		Vector3<float> mySpecular;
	};
}namespace CU = CommonUtilities;
