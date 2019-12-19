#pragma once


#pragma once

#include "Vector3f.h"
#include "IPrimitive.h"
#include "Ray.h"
#include <cmath> 

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

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const
	{
		// plane normals
		Vector3 v0v1 = mV1 - mV0;
		Vector3 v0v2 = mV2 - mV1;

		Vector3 N = cross(v0v1, v0v2);
		float area2 = N.length();

		// Step 1: finding P
		float NdotRayDirection = dot(N, ray.direction());
		// calculates the absolute value
		if (std::fabs(NdotRayDirection) < 1e-8) // near zero
			return false; // ray and triangle are parallel, so they do not intersect

		// compute component d
		float d = dot(N, mV0);

		// compute t
		rec.t = (dot(N, ray.origin()) + d) / NdotRayDirection;


		// check if the triangle is behind the ray
		if (rec.t < 0) return false;

		rec.p = ray.origin() + rec.t * ray.direction();

		// Step 2: inside, outside test
		Vector3 C;

		// edge0
		Vector3 edge0 = mV1 - mV0;
		Vector3 vp0 = rec.p - mV0;
		C = cross(edge0, vp0);
		if (dot(N, C) < 0) return false;

		// edge1
		Vector3 edge1 = mV2 - mV1;
		Vector3 vp1 = rec.p - mV1;
		C = cross(edge1, vp1);
		if (dot(N, C) < 0) return false;

		// edge2
		Vector3 edge2 = mV0 - mV2;
		Vector3 vp2 = rec.p - mV2;
		C = cross(edge2, vp2);
		if (dot(N, C) < 0) return false;

		if (NdotRayDirection < 0)
		{
			rec.normal = -N;
		}
		else
		{
			rec.normal = N;
		}

		return true; // ray hits the triangle
	}
};