#include "Model.h"


CU::Model::Model()
{
	myVoxels.Init(4);
	myChildren.Init(4);
	//Vector4<float> translate = myLocalSpace.GetTranslation();
	//myLocalSpace = Matrix44<float>::CreateRotateAroundX(3.14f);
	//myLocalSpace.SetTranslation(Vector4<float>(0,7,16,1));
}


CU::Model::~Model()
{

}

void CU::Model::AddChild(Model &aModel)
{
	myChildren.Add(&aModel);
}

void CU::Model::AddPoint(const Voxel &aVoxel) 
{
	myVoxels.Add(aVoxel);
}

void CU::Model::CreateCullingMesh()
{
	for (unsigned short i = 0; i < myVoxels.Size(); ++i)
	{
		if (i == 0)
		{
			myCullingMesh.myCenterPosition = myVoxels[i].myPosition;
		}
		else
		{
			myCullingMesh.myCenterPosition += myVoxels[i].myPosition;
			myCullingMesh.myCenterPosition /= 2.f;
		}
	}
	Vector3<float> toCenter;
	for (unsigned short i = 0; i < myVoxels.Size(); ++i)
	{
		toCenter = myCullingMesh.myCenterPosition - myVoxels[i].myPosition;
		if (Length(toCenter) > myCullingMesh.myRadius)
		{
			myCullingMesh.myRadius = Length(toCenter);
		}
	}
}

CU::Intersection::Sphere& CU::Model::GetCullingMesh()
{
	return myCullingMesh;
}

CU::GrowingArray<CU::Model*>& CU::Model::GetChild()
{
	return myChildren;
}

const CU::Voxel& CU::Model::GetPoint(unsigned short aIndex) const
{
	return myVoxels[aIndex];
}

const CU::Matrix44<float>& CU::Model::GetSpace() const
{
	return myLocalSpace;
}

unsigned short CU::Model::GetModelSize() const
{
	return static_cast<unsigned short>(myVoxels.Size());
}

void CU::Model::SetRotationX(const float aRadians)
{
	myLocalSpace.SetRotationX(aRadians);
}

void CU::Model::RotateX(const float aRadians)
{
	myLocalSpace.RotateX(aRadians);
}

void CU::Model::SetRotationY(const float aRadians)
{
	myLocalSpace.SetRotationY(aRadians);
}

void CU::Model::RotateY(const float aRadians)
{
	myLocalSpace.RotateY(aRadians);
}

void CU::Model::SetRotationZ(const float aRadians)
{
	myLocalSpace.SetRotationZ(aRadians);
}

void CU::Model::RotateZ(const float aRadians)
{
	myLocalSpace.RotateZ(aRadians);
}

void CU::Model::SetPosition(const Vector3<float> &aPosition)
{
	myLocalSpace.SetTranslation(Vector4<float>(aPosition.myX, aPosition.myY, aPosition.myZ, 1.f));
}

void CU::Model::AddPosition(const Vector3<float> &aPosition)
{
	Vector4<float> translation(myLocalSpace.GetTranslation());
	translation += Vector4<float>(aPosition.myX, aPosition.myY, aPosition.myZ, 1.f);
	myLocalSpace.SetTranslation(translation);
}