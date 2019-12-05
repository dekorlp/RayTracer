#pragma once

#include "Vector3f.h"
#include "IPrimitive.h"
#include <cmath> 

class Sphere : public IPrimitive
{
public:
	float radius, radius2;                  /// sphere radius and radius^2 
	Sphere(
		const Vec3f &c,
		const float &r,
		const Vec3f &sc,
		const float &refl = 0,
		const float &transp = 0,
		const Vec3f &ec = 0) :
		radius(r), radius2(r * r)
	{ 
		center = c;
		surfaceColor = sc;
		emissionColor = ec;
		transparency = transp;
		reflection = refl;
	}

	/*bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const
	{
		Vec3f oc =rayorig - center;
		float a = raydir.dot(raydir);
		float b = 2.0 * oc.dot(raydir);
		float c = oc.dot(oc) - radius*radius;
		float discriminant = b*b - 4 * a*c;
		if (discriminant < 0) {
			return false;
		}
		else {
			t0 = (-b - sqrt(discriminant)) / (2.0*a);
			t1 = t0;
			return true;
		}
	}*/

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
	}
};