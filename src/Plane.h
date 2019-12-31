#pragma once

#include <vector>
#include "Vector3.h"
#include "Triangle.h"
#include "Matrix.h"

class Plane
{
public:
	Plane(std::vector<unsigned int> triangles, std::vector<IPrimitive*> *primitives);
	void rotateX(float degree);
	void rotateY(float degree);
	void rotateZ(float degree);
	void Move(Vector3& position);
private:
	std::vector<unsigned int> mIndexOfTriangle;
	std::vector<IPrimitive*> *mPrimitives;
};