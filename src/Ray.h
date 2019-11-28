#pragma once

#include "Vector3.h"

class Ray
{
private:
	Vector3 m_Start;
	Vector3 m_Direction;

public:
	Ray(Vector3 &start, Vector3 &direction);

	Vector3 GetStart();

	Vector3 GetDirection();
	
};