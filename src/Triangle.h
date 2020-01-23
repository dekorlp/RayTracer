#pragma once


#pragma once

#include "IPrimitive.h"
#include "Ray.h"

class Triangle : public IPrimitive
{
public:
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

		Vector3 v0v1 = mV1 - mV0;
		Vector3 v0v2 = mV2 - mV0;

		Vector3 N = cross(v0v1, v0v2);

		normal = unit_vector(N);
	}

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const;
};