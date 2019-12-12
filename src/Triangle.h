#pragma once


#pragma once

#include "Vector3f.h"
#include "IPrimitive.h"
#include "Ray.h"
#include <cmath> 

class Triangle : public IPrimitive
{
public:
	float radius;                  /// sphere radius and radius^2 
	Triangle(
		const Vector3 &c,
		const float &r,
		const Vector3 &sc,
		const float &refl = 0,
		const float &transp = 0)
	{
		center = c;
		surfaceColor = sc;
		transparency = transp;
		reflection = refl;
	}

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
				return true;
			}

			temp = (-b + sqrt(b*b - a*c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = ray.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
		}
		return false;
	}
};