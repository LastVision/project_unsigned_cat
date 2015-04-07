#pragma once
#include "Vector.h"
namespace CommonUtilities
{
	namespace Intersection
	{
		struct Circle
		{
		public:
			Vector2<float> myCenterPosition;
			float myRadius;
			float myRadiusSquared;
		};
	};
}
namespace CU = CommonUtilities;