#pragma once


#pragma once

#include "IPrimitive.h"
#include "Ray.h"

class TrianglePBR : public IPrimitive
{
public:
	TrianglePBR(
		const Vector3& v0,
		const Vector3& v1,
		const Vector3& v2,
		const Vector3& sc,
		const float metallic = 0, 
		float roughness = 0, 
		float ambientOcclusion = 0)
	{
		mV0 = v0;
		mV1 = v1;
		mV2 = v2;
		surfaceColor = sc;
		mMetallic = metallic;
		mRroughness = roughness;
		mAmbientOcclusion = ambientOcclusion;
	}

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const;
};