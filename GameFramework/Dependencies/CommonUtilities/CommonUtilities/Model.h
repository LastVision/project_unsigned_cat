#pragma once
#include "Voxel.h"
#include "Matrix.h"
#include "GrowingArray.h"
#include "Intersection.h"
namespace CommonUtilities
{
	class Model
	{
	public:
		Model();
		~Model();

		void AddPoint(const Voxel &aVoxel);
		const Voxel& GetPoint(unsigned short aIndex) const;

		void AddChild(Model &aModel);
		CU::GrowingArray<Model*>& GetChild();
		void CreateCullingMesh();

		CU::Intersection::Sphere& GetCullingMesh();

		void SetRotationX(const float aRadians);
		void RotateX(const float aRadians);
		void SetRotationY(const float aRadians);
		void RotateY(const float aRadians);
		void SetRotationZ(const float aRadians);
		void RotateZ(const float aRadians);

		void SetPosition(const Vector3<float> &aPosition);
		void AddPosition(const Vector3<float> &aPosition);

		unsigned short GetModelSize() const;

		const Matrix44<float>& GetSpace() const;
	private:
		GrowingArray<Voxel> myVoxels;
		Matrix44<float> myLocalSpace;
		CU::GrowingArray<Model*> myChildren;
		CU::Intersection::Sphere myCullingMesh;
	};

} namespace CU = CommonUtilities;

