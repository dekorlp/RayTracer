#pragma once

#include "IPrimitive.h"
#include "Ray.h"

class SpherePBR : public IPrimitive
{
public:
	float radius;                  /// sphere radius and radius^2 
	Vector3 center;                /// position of the sphere

	SpherePBR(
		const Vector3 &c,
		const float &r,
		const Vector3 &sc,
		const float metallic = 0,
		float roughness = 0,
		float ambientOcclusion = 0) :
		radius(r)
	{
		center = c;
		surfaceColor = sc;
		mMetallic = metallic;
		mRroughness = roughness;
		mAmbientOcclusion = ambientOcclusion;
	}


	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const;
};