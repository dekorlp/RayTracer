#pragma once

#include "IPrimitive.h"
#include "Ray.h"
#include <cmath> 

class Sphere : public IPrimitive
{
public:
	float radius;                  /// sphere radius and radius^2 
	Vector3 center;                /// position of the sphere

	Sphere(
		const Vector3 &c,
		const float &r,
		const Vector3 &sc,
		const float &reflection = 0) :
		radius(r)
	{ 
		center = c;
		surfaceColor = sc;
		mReflection = reflection;
	}

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const;
};