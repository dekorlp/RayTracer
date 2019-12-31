#pragma once

#include "Vector3.h"
#include "Ray.h"

struct hit_record
{
	float t;
	Vector3 p;
	Vector3 normal;
};

class IPrimitive
{
public:
	Vector3 surfaceColor, emissionColor;      /// surface color and emission (light) 
	float mReflection;         /// surface transparency and reflectivity 
	
	// physical based rendering
	float mMetallic;
	float mRroughness;
	float mAmbientOcclusion;

	virtual bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const = 0;
};