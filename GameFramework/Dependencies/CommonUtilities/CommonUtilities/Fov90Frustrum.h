#pragma once

#include "PlaneVolume.h"
#include "Matrix.h"

namespace CommonUtilities
{
	namespace Intersection
	{
		struct Fov90Frustrum
		{
			inline Fov90Frustrum();
			inline Fov90Frustrum(float aNearPlane, float aFarPlane);
			inline ~Fov90Frustrum();
			inline void Init(float aNearPlane, float aFarPlane);
			inline const PlaneVolume<float>& GetMyPlaneVolume() const;
			inline const Vector3<float>& GetMyMiddle()const;
		private:
			float myNearPlane;
			float myFarPlane;
			Vector3<float> myMiddle;
			PlaneVolume<float> myFrustum;
		};
	};
}
namespace CU = CommonUtilities;

CU::Intersection::Fov90Frustrum::Fov90Frustrum()
{

}

CU::Intersection::Fov90Frustrum::Fov90Frustrum(float aNearPlane, float aFarPlane)
{
	Init(aNearPlane, aFarPlane);
}

CU::Intersection::Fov90Frustrum::~Fov90Frustrum()
{

}

void CU::Intersection::Fov90Frustrum::Init(float aNearPlane, float aFarPlane)
{
	myNearPlane = aNearPlane;
	myFarPlane = aFarPlane;
	float rotate45 = sqrt(2.0f) / 2.f;
	float middle = ((myFarPlane - myNearPlane) / 2);
	myMiddle = Vector3<float>(0, 0, middle);

	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, myNearPlane), Vector3<float>(0, 0, -1))); // Near
	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, myFarPlane), Vector3<float>(0, 0, 1))); // Far
	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, 0), Vector3<float>(rotate45, 0, -rotate45))); // Right
	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, 0), Vector3<float>(-rotate45, 0, -rotate45))); // Left
	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, 0), Vector3<float>(0, rotate45, -rotate45))); //Up
	myFrustum.AddPlane(Plane<float>(Vector3<float>(0, 0, 0), Vector3<float>(0, -rotate45, -rotate45))); //Down
}

const CU::PlaneVolume<float>& CU::Intersection::Fov90Frustrum::GetMyPlaneVolume() const
{
	return myFrustum;
}


const Vector3<float>& CU::Intersection::Fov90Frustrum::GetMyMiddle() const
{
	return myMiddle;
}
