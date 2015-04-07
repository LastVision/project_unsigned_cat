#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "AABB.h"
#include "LineSegment3D.h"
#include "LineSegment2D.h"
#include "Fov90Frustrum.h"
#include "PlaneVolume.h"
#include "LineVolume.h"
#include "Circle.h"
#include "GrowingArray.h"
#include <vector>

namespace CommonUtilities
{
	namespace Intersection
	{
		template <typename Type>
		inline bool PointInsideSphere(const Sphere &aSphere, const Vector3<Type> &aPoint);

		template <typename Type>
		inline bool PointInsideAABB(const AABB &aAABB, const Vector3<Type> &aPoint);

		inline bool LineVsSphere(const LineSegment3D &aLine, const Sphere &aSphere, Vector3<float> &anInterserctionPoint);
		inline bool SwepthSphereVsSphere(const LineSegment3D &aLine, float aRadius, const Sphere &aSphere);

		inline bool SwepthSphereVsAABB(const LineSegment3D &aLine, float aRadius, const AABB &aAABB);
		inline bool LineVsAABB(const LineSegment3D &aLine, const AABB &aAABB, Vector3<float> &anInterserctionPoint);

		inline bool SphereVsFrustrum(const Sphere &aSphere, const Fov90Frustrum &aFrust);

		inline bool LineVsLine(LineSegment2D aLineOne, LineSegment2D aLineTwo,Vector2<float> &anInterserctionPoint);

		inline int PlaneVsSphere(const Plane<float> &aPlane, const Sphere &aSphere);

		inline Vector2<float> GetClosestPointFromLine(const LineSegment2D &aLine, const Vector2<float> &aCenterPointOfCircle);
	};
}
namespace CU = CommonUtilities;

template <typename Type>
bool CU::Intersection::PointInsideSphere(const Sphere &aSphere, const Vector3<Type> &aPoint)
{
	Vector3<Type> lengthBetween;
	lengthBetween = aSphere.myCenterPosition - aPoint;
	if (Length(lengthBetween) < aSphere.myRadius)
	{
		return true;
	}
	return false;
}

template <typename Type>
bool CU::Intersection::PointInsideAABB(const AABB &aAABB, const Vector3<Type> &aPoint)
{
	PlaneVolume<Type> tempAABBvolume;
	Plane<Type> aPlane;

	aPlane.InitWithPointAndNormal(aAABB.myMinPos, Vector3<float>(0.f, 0, -1));
	tempAABBvolume.AddPlane(aPlane);

	aPlane.InitWithPointAndNormal(aAABB.myMinPos, Vector3<float>(-1, 0, 0));
	tempAABBvolume.AddPlane(aPlane);

	aPlane.InitWithPointAndNormal(aAABB.myMinPos, Vector3<float>(0, -1, 0));
	tempAABBvolume.AddPlane(aPlane);

	aPlane.InitWithPointAndNormal(aAABB.myMaxPos, Vector3<float>(0, 0, 1));
	tempAABBvolume.AddPlane(aPlane);

	aPlane.InitWithPointAndNormal(aAABB.myMaxPos, Vector3<float>(1, 0, 0));
	tempAABBvolume.AddPlane(aPlane);

	aPlane.InitWithPointAndNormal(aAABB.myMaxPos, Vector3<float>(0, 1, 0));
	tempAABBvolume.AddPlane(aPlane);


	if (tempAABBvolume.Inside(aPoint) == true)
	{

		return true;
	}
	return false;
}

bool CU::Intersection::LineVsSphere(const LineSegment3D &aLine, const Sphere &aSphere, Vector3<float> &anInterserctionPoint)
{
	Vector3<float> lengthBetween;
	Vector3<float> lineMaxLength;
	Vector3<float> lineNormal;
	Vector3<float> toClosest;
	Vector3<float> closestPoint;
	float d = 0;

	lengthBetween = aSphere.myCenterPosition - aLine.myStartPos;

	lineNormal = aLine.myEndPos - aLine.myStartPos;
	lineMaxLength = lineNormal;
	Normalize(lineNormal);

	d = Dot(lengthBetween, lineNormal);

	closestPoint = aLine.myStartPos + lineNormal * d;
	if (Length(closestPoint - aLine.myStartPos) > Length(lineMaxLength))
	{
		closestPoint = aLine.myEndPos;
	}
	else if (Length(closestPoint - aLine.myStartPos) < 0)
	{
		closestPoint = aLine.myStartPos;
	}
	toClosest = aSphere.myCenterPosition - closestPoint;

	if (Length(toClosest) < aSphere.myRadius)
	{
		anInterserctionPoint = closestPoint;
		return true;
	}
	return false;
}

bool CU::Intersection::SwepthSphereVsSphere(const LineSegment3D &aLine, float aRadius, const Sphere &aSphere)
{
	Vector3<float> lengthBetween;
	Vector3<float> lineNormal;
	Vector3<float> closestPoint;
	float d = 0;

	lengthBetween = aSphere.myCenterPosition - aLine.myStartPos;

	lineNormal = aLine.myEndPos - aLine.myStartPos;
	Normalize(lineNormal);

	d = Dot(lengthBetween, lineNormal);

	closestPoint = aLine.myStartPos + lineNormal * d;

	if (Length(aSphere.myCenterPosition - closestPoint) < aSphere.myRadius + aRadius)
	{
		return true;
	}
	return false;
}

bool CU::Intersection::SwepthSphereVsAABB(const LineSegment3D &aLine, float aRadius, const AABB &aAABB)
{
	Vector3<float> lengthBetween;
	Vector3<float> lineNormal;
	Vector3<float> closestPoint;
	Vector3<float> lineMaxLength;

	const int amountOfCorners = 8;
	GrowingArray<Vector3<float>, int> arrayOfCorners;
	arrayOfCorners.Init(amountOfCorners);


	arrayOfCorners.Add(aAABB.myMinPos);
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMinPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMaxPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMinPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMaxPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMinPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMaxPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(aAABB.myMaxPos);

	float d = 0;

	for (int i = 0; i < amountOfCorners; i++)
	{
		lengthBetween = arrayOfCorners[i] - aLine.myStartPos;
		lineNormal = aLine.myEndPos - aLine.myStartPos;
		lineMaxLength = lineNormal;
		Normalize(lineNormal);

		d = Dot(lengthBetween, lineNormal);

		closestPoint = aLine.myStartPos + lineNormal * d;

		if (Length(closestPoint - aLine.myStartPos) > Length(lineMaxLength))
		{
			closestPoint = aLine.myEndPos;
		}
		else if (Length(closestPoint - aLine.myStartPos) < 0)
		{
			closestPoint = aLine.myStartPos;
		}

		Sphere aSphere;
		aSphere.myCenterPosition = closestPoint;
		aSphere.myRadius = aRadius;
aSphere.myRadiusSquared = aRadius * aRadius;

if (PointInsideSphere(aSphere, arrayOfCorners[i]) == true)
{
	return true;
}
else if (PointInsideAABB<float>(aAABB, closestPoint) == true)
{
	return true;
}
	}
	return false;
}

bool CU::Intersection::LineVsAABB(const LineSegment3D &aLine, const AABB &aAABB, Vector3<float> &anInterserctionPoint)
{
	Vector3<float> lengthBetween;
	Vector3<float> lineNormal;
	Vector3<float> closestPoint;
	Vector3<float> lineMaxLength;

	const int amountOfCorners = 8;
	GrowingArray<Vector3<float>, int> arrayOfCorners;
	arrayOfCorners.Init(amountOfCorners);


	arrayOfCorners.Add(aAABB.myMinPos);
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMinPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMaxPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMinPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMaxPos.myY, aAABB.myMinPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMaxPos.myX, aAABB.myMinPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(Vector3<float>(aAABB.myMinPos.myX, aAABB.myMaxPos.myY, aAABB.myMaxPos.myZ));
	arrayOfCorners.Add(aAABB.myMaxPos);

	float d = 0;

	for (int i = 0; i < amountOfCorners; i++)
	{
		lengthBetween = arrayOfCorners[i] - aLine.myStartPos;
		lineNormal = aLine.myEndPos - aLine.myStartPos;
		lineMaxLength = lineNormal;
		Normalize(lineNormal);

		d = Dot(lengthBetween, lineNormal);

		closestPoint = aLine.myStartPos + lineNormal * d;

		if (Length(closestPoint - aLine.myStartPos) > Length(lineMaxLength))
		{
			closestPoint = aLine.myEndPos;
		}
		else if (Length(closestPoint - aLine.myStartPos) < 0)
		{
			closestPoint = aLine.myStartPos;
		}

		if (PointInsideAABB<float>(aAABB, closestPoint) == true)
		{
			anInterserctionPoint = closestPoint;
			return true;
		}
	}
	return false;
}

bool CU::Intersection::SphereVsFrustrum(const Sphere &aSphere, const Fov90Frustrum &aFrust)
{
	for (unsigned short i = 0; i < aFrust.GetMyPlaneVolume().GetPlaneList().Size(); ++i)
	{
		if (PlaneVsSphere(aFrust.GetMyPlaneVolume().GetPlaneList()[i], aSphere) > 0)
		{
			return false;
		}
	}
	return true;

}

bool CU::Intersection::LineVsLine(LineSegment2D aLineOne, LineSegment2D aLineTwo, Vector2<float> &anInterserctionPoint)
{
	CU::Line<float> lineOne(aLineOne.myStartPos, aLineOne.myEndPos);
	CU::Line<float> lineTwo(aLineTwo.myStartPos, aLineTwo.myEndPos);

	float numX = lineTwo.GetAbc().myY * lineOne.GetAbc().myZ - lineOne.GetAbc().myY * lineTwo.GetAbc().myZ;
	float denX = lineOne.GetAbc().myX * lineTwo.GetAbc().myY - lineTwo.GetAbc().myX * lineOne.GetAbc().myY;

	float numY = lineTwo.GetAbc().myX * lineOne.GetAbc().myZ - lineOne.GetAbc().myX * lineTwo.GetAbc().myZ;
	float denY = lineTwo.GetAbc().myX * lineOne.GetAbc().myY - lineOne.GetAbc().myX * lineTwo.GetAbc().myY;

	if (denX == 0 && denY == 0)
	{
		if (lineOne.GetAbc().myZ != lineTwo.GetAbc().myZ)
		{
			return false;
		}
		Vector2<float> directionOne = aLineOne.myEndPos - aLineOne.myStartPos;
		Vector2<float> directionTwo = aLineTwo.myEndPos - aLineTwo.myStartPos;

		float lengthDirectionOne = Length(directionOne);
		directionOne /= lengthDirectionOne;

		float lengthDirectionTwo = Length(directionTwo);
		directionTwo /= lengthDirectionTwo;

		if (Dot(directionOne, aLineTwo.myEndPos - aLineOne.myStartPos) < lengthDirectionOne && Dot(directionOne, aLineTwo.myEndPos - aLineOne.myStartPos) > 0)
		{
			anInterserctionPoint = aLineTwo.myEndPos;
			return true;
		}
		if (Dot(directionOne, aLineTwo.myStartPos - aLineOne.myStartPos) < lengthDirectionOne && Dot(directionOne, aLineTwo.myStartPos - aLineOne.myStartPos) > 0)
		{
			anInterserctionPoint = aLineOne.myStartPos;
			return true;
		}
		if (Dot(directionTwo, aLineOne.myEndPos - aLineTwo.myStartPos) < lengthDirectionTwo && Dot(directionTwo, aLineOne.myEndPos - aLineTwo.myStartPos) > 0)
		{
			anInterserctionPoint = aLineOne.myEndPos;
			return true;
		}
		if (Dot(directionTwo, aLineOne.myStartPos - aLineTwo.myStartPos) < lengthDirectionTwo && Dot(directionTwo, aLineOne.myStartPos - aLineTwo.myStartPos) > 0)
		{
			anInterserctionPoint = aLineOne.myStartPos;
			return true;
		}
		return false;
	}
	anInterserctionPoint = Vector2<float>(numX / denX, numY / denY);
	Vector2<float> vectorOne(aLineOne.myEndPos - aLineOne.myStartPos);
	Vector2<float> vectorOneintersect(anInterserctionPoint - aLineOne.myStartPos);

	if (Dot(vectorOne, vectorOneintersect) < 0 || Length2(vectorOneintersect) > Length2(vectorOne))
	{
		return false;
	}
	Vector2<float> vectorTwo(aLineTwo.myEndPos - aLineTwo.myStartPos);
	Vector2<float> vectorTwointersect(anInterserctionPoint - aLineTwo.myStartPos);

	if (Dot(vectorTwo, vectorTwointersect) < 0 || Length2(vectorTwointersect) > Length2(vectorTwo))
	{
		return false;
	}
	return true;
}

int CU::Intersection::PlaneVsSphere(const Plane<float> &aPlane, const Sphere &aSphere)
{
	float d = Dot(aPlane.GetNormal(), aSphere.myCenterPosition) - aPlane.GetAbcd().myW;
	if (d >= aSphere.myRadius)
	{
		return 1;
	}
	if (d <= -aSphere.myRadius)
	{
		return -1;
	}
	return 0;
}


Vector2<float> CU::Intersection::GetClosestPointFromLine(const LineSegment2D &aLine, const Vector2<float> &aCenterPointOfCircle)
{
	Vector2<float> lengthBetween;
	Vector2<float> lineMaxLength;
	Vector2<float> lineNormal;
	Vector2<float> closestPoint;
	float d = 0;

	lengthBetween = aCenterPointOfCircle - aLine.myStartPos;

	lineNormal = aLine.myEndPos - aLine.myStartPos;
	lineMaxLength = lineNormal;
	Normalize(lineNormal);

	d = Dot(lengthBetween, lineNormal);

	closestPoint = aLine.myStartPos + lineNormal * d;
	if (Length(closestPoint - aLine.myStartPos) > Length(lineMaxLength))
	{
		closestPoint = aLine.myEndPos;
	}
	else if (Length(closestPoint - aLine.myStartPos) < 0)
	{
		closestPoint = aLine.myStartPos;
	}
	return closestPoint;
}
