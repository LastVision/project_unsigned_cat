#include "BaseLight.h"

CU::BaseLight::BaseLight()
{

}

CU::BaseLight::~BaseLight()
{

}

Vector3<float> CU::BaseLight::Diffuse(Vector3<float> aNormal, Vector3<float> aLightDirection, Vector3<float> aVoxelColor, Vector3<float> aLightColor)
{
	return aVoxelColor * aLightColor * Saturate(Dot(aNormal, (aLightDirection * -1.f)));
}

Vector3<float> CU::BaseLight::Specular(Vector3<float> aHalfAngle, Vector3<float> aNormal, float aSpecularPower, Vector3<float> aLightColor)
{
	return aLightColor * pow(Saturate(Dot(aHalfAngle, aNormal)), aSpecularPower);
}

Vector3<float> CU::BaseLight::GetColor(Voxel aVoxel, Vector3<float> aCameraNormal)
{
	myDiffuse = Diffuse(aVoxel.myNormal, myLightDirection, aVoxel.myColor, myLightColor);
	mySpecular = Specular(GetHalfAngle(aCameraNormal, myLightDirection), aVoxel.myNormal, mySpecularPower, myLightColor);
	return Vector3<float>(Saturate(myDiffuse.myX + mySpecular.myX), Saturate(myDiffuse.myY + mySpecular.myY), Saturate(myDiffuse.myZ + mySpecular.myZ));
}

Vector3<float> CU::BaseLight::GetHalfAngle(Vector3<float> aCameraNormal, Vector3<float> aLightDirection)
{
	Vector3<float> halfAngleVector = (aCameraNormal + (aLightDirection * -1.f)) / 2.0f;
	Normalize(halfAngleVector);
	return halfAngleVector;
}

float CU::BaseLight::Saturate(float aDotProduct)
{
	if (aDotProduct > 1)
	{
		return 1;
	}
	else if (aDotProduct < 0)
	{
		return 0;
	}
	else
	{
		return aDotProduct;
	}
}