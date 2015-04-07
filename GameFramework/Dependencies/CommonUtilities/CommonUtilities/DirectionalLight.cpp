#include "DirectionalLight.h"

CU::DirectionalLight::DirectionalLight()
{

}

CU::DirectionalLight::~DirectionalLight()
{

}

void CU::DirectionalLight::Update(Vector3<float> aDirection, Vector3<float> aColor, float aSpecularPower)
{
	myLightColor = aColor;
	myLightDirection = aDirection;
	mySpecularPower = aSpecularPower;
}