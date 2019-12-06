#pragma once

#include "Vector3.h"
#include "Ray.h"

class IPrimitive
{
public:
	Vector3 surfaceColor, emissionColor;      /// surface color and emission (light) 
	float transparency, reflection;         /// surface transparency and reflectivity 
	Vector3 center;                           /// position of the sphere 

	virtual bool intersect(Ray& ray) const = 0;
};