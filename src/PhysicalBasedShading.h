#pragma once
#include "Vector3.h"

# define PI           3.14159265358979323846  /* pi */

class PhysicalBasedShading
{
public:
	static float TrowbridgeReitzDistributionGGX(Vector3& m, Vector3& n, float roughness);
	static float GeometrySchlickGGX(Vector3& n, Vector3& v, float roughness);
	static Vector3 FresnelSchlick(Vector3& v, Vector3& h, Vector3& F0);
};