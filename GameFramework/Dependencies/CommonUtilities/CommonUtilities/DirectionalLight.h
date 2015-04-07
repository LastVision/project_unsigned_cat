#pragma once
#include "BaseLight.h"
namespace CommonUtilities
{
	class DirectionalLight : public BaseLight
	{
	public:
		DirectionalLight();
		~DirectionalLight();
		
		void Update(Vector3<float> aDirection, Vector3<float> aColor, float aSpecularPower);
		inline const Vector3<float>& GetLightDirection() const;
	};

	const Vector3<float>& DirectionalLight::GetLightDirection() const
	{
		return myLightDirection;
	}
}namespace CU = CommonUtilities;