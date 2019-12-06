#pragma once

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vector3& origin, const Vector3 &direction) { mOrigin = origin; mDirection = direction; }
	Vector3 origin() { return mOrigin; }
	Vector3 direction() { return mDirection; }
	Vector3 point_at_parameter(float t) { return mOrigin + t * mDirection; };

private:
	Vector3 mOrigin;
	Vector3 mDirection;
	
};