#pragma once
template <typename TYPE>
class Vector3
{
public:
	Vector3();
	Vector3(TYPE aX, TYPE aY, TYPE aZ);
	union
	{
		TYPE myX;
		TYPE x;
		TYPE r;
		TYPE myR;
	};
	union
	{
		TYPE myY;
		TYPE y;
		TYPE g;
		TYPE myG;
	};
	union
	{
		TYPE myZ;
		TYPE z;
		TYPE b;
		TYPE myB;
	};
};
template<typename TYPE>
Vector3<TYPE>::Vector3()
{
	myX = 0;
	myY = 0;
	myZ = 0;
}

template<typename TYPE>
Vector3<TYPE>::Vector3(TYPE aX, TYPE aY, TYPE aZ)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
}