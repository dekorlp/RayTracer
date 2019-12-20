#pragma once


#pragma once

#include "IPrimitive.h"
#include "Ray.h"

class Triangle : public IPrimitive
{
public:
	Vector3 mV0;
	Vector3 mV1;
	Vector3 mV2;
	Triangle(
		const Vector3& v0,
		const Vector3& v1,
		const Vector3& v2,
		const Vector3& sc,
		const float& reflection = 0)
	{
		mV0 = v0;
		mV1 = v1;
		mV2 = v2;
		surfaceColor = sc;
		mReflection = reflection;
	}

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const;
};