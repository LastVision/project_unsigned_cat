#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	namespace Intersection
	{
		struct LineSegment3D
		{
			Vector3<float> myStartPos;
			Vector3<float> myEndPos;
		};
	};
}
namespace CU = CommonUtilities;