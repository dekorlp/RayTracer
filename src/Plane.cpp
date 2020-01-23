#include "Plane.h"

Plane::Plane(std::vector<unsigned int> triangles, std::vector<IPrimitive*> *primitives)
{
	mIndexOfTriangle = triangles;
	mPrimitives = primitives;
}

void Plane::rotateX(float degree)
{
	for (unsigned int i = 0; i < mIndexOfTriangle.size(); i++)
	{
		IPrimitive& triangle = *mPrimitives->at(mIndexOfTriangle[i]);
		

		Matrix mat = Matrix::RotateX(degree);
		triangle.mV0 = mat.multiply(1, triangle.mV0);
		triangle.mV1 = mat.multiply(1, triangle.mV1);
		triangle.mV2 = mat.multiply(1, triangle.mV2);

		triangle.normal = mat.multiply(1, triangle.normal);
	}
}

void Plane::rotateY(float degree)
{
	for (unsigned int i = 0; i < mIndexOfTriangle.size(); i++)
	{
		IPrimitive& triangle = *mPrimitives->at(mIndexOfTriangle[i]);


		Matrix mat = Matrix::RotateY(degree);
		triangle.mV0 = mat.multiply(1, triangle.mV0);
		triangle.mV1 = mat.multiply(1, triangle.mV1);
		triangle.mV2 = mat.multiply(1, triangle.mV2);

		triangle.normal = mat.multiply(1, triangle.normal);
	}
}


void Plane::rotateZ(float degree)
{
	for (unsigned int i = 0; i < mIndexOfTriangle.size(); i++)
	{
		IPrimitive& triangle = *mPrimitives->at(mIndexOfTriangle[i]);


		Matrix mat = Matrix::RotateZ(degree);
		triangle.mV0 = mat.multiply(1, triangle.mV0);
		triangle.mV1 = mat.multiply(1, triangle.mV1);
		triangle.mV2 = mat.multiply(1, triangle.mV2);

		triangle.normal = mat.multiply(1, triangle.normal);
	}
}


void Plane::Move(Vector3& position)
{
	for (unsigned int i = 0; i < mIndexOfTriangle.size(); i++)
	{
		IPrimitive& triangle = *mPrimitives->at(mIndexOfTriangle[i]);


		triangle.mV0 = position + triangle.mV0;
		triangle.mV1 = position + triangle.mV1;
		triangle.mV2 = position + triangle.mV2;
	}
}