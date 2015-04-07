#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	namespace Intersection
	{
		
		struct Sphere
		{
		public:
			Vector3<float> myCenterPosition;
			float myRadius = 0.f;
			float myRadiusSquared = myRadius * myRadius;
		};
	};
}
namespace CU = CommonUtilities;