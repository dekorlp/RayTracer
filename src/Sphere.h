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

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const
	{
		Vector3 oc = ray.origin() - center;
		float a = dot(ray.direction(), ray.direction());
		float b = dot(oc, ray.direction());
		float c = dot(oc, oc) - radius * radius;
		float discriminant = b*b - a*c;
		if (discriminant > 0)
		{
			float temp = (-b - sqrt(b*b - a*c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = ray.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.color = surfaceColor;
				return true;
			}

			temp = (-b + sqrt(b*b - a*c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = ray.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.color = surfaceColor;
				return true;
			}
		}
		return false;
	}
};