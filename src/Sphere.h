#pragma once

#include "Vector3f.h"
#include "IPrimitive.h"
#include "Ray.h"
#include <cmath> 

class Sphere : public IPrimitive
{
public:
	float radius;                  /// sphere radius and radius^2 
	Sphere(
		const Vector3 &c,
		const float &r,
		const Vector3 &sc,
		const float &refl = 0,
		const float &transp = 0,
		const Vector3 &ec = Vector3(0.0, 0.0, 0.0)) :
		radius(r)
	{ 
		center = c;
		surfaceColor = sc;
		emissionColor = ec;
		transparency = transp;
		reflection = refl;
	}

	/*
	bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0) const
	{
		float t1 = 0;
		Vec3f l = center - rayorig;
		float tca = l.dot(raydir);
		if (tca < 0) return false;
		float d2 = l.dot(l) - tca * tca;
		if (d2 > radius2) return false;
		float thc = sqrt(radius2 - d2);
		t0 = tca - thc;
		t1 = tca + thc;
		if (t0 < 0) t0 = t1;

		return true;
	}*/

	bool intersect(Ray& ray) const
	{
		Vector3 oc = ray.origin() - center;
		float a = dot(ray.direction(), ray.direction());
		float b = 2.0 * dot(oc, ray.direction());
		float c = dot(oc, oc) - radius * radius;
		float discriminant = b*b - 4 * a*c;
		return discriminant > 0;
	}
};