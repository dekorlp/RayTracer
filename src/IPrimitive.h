#pragma once

#include "Vector3f.h"

class IPrimitive
{
public:
	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light) 
	float transparency, reflection;         /// surface transparency and reflectivity 
	Vec3f center;                           /// position of the sphere 

	virtual bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0) const = 0;
};