#pragma once

#include "Vector3.h"
#include "Ray.h"

struct hit_record
{
	float t;
	Vector3 p;
	Vector3 normal;
	Vector3 color;
};

class IPrimitive
{
public:
	Vector3 surfaceColor, emissionColor;      /// surface color and emission (light) 
	float transparency, reflection;         /// surface transparency and reflectivity 
	Vector3 center;                           /// position of the sphere 

	virtual bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const = 0;
};