#include "PhysicalBasedShading.h"
#include <algorithm>

float PhysicalBasedShading::TrowbridgeReitzDistributionGGX(Vector3& m, Vector3& n, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float numerator = a2;

	float dotNM = std::max(dot(n, m), 0.0f);
	float dotNM2 = dotNM * dotNM;
	float denominator = (dotNM2 * (a2 - 1.0) + 1.0);

	float d = numerator / (PI * (denominator * denominator));

	return d;

}

float PhysicalBasedShading::GeometrySchlickGGX(Vector3& n, Vector3& v, float roughness)
{
	float a = (roughness + 1) * (roughness + 1);
	float k = a / 8.0;
	float dNV = std::max(dot(n, v), 0.0f);
	float numerator = dNV;
	float denominator = dNV * (1 - k) + k;
	float g = numerator / denominator;
	return g;
}

Vector3 PhysicalBasedShading::FresnelSchlick(Vector3& v, Vector3& h, Vector3& F0)
{
	float dotVH = std::max(dot(v, h), 0.0f);
	return F0 + (Vector3(1.0, 1.0, 1.0) - F0) * pow(1.0 - dotVH, 5.0);
}