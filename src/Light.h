#pragma once
#include "Vector3.h"

class Light
{
public:
	Light(Vector3& color, Vector3& position, float emissionStrength) { m_Color = color; m_Position = position; m_emissionStrength = emissionStrength; }
	Vector3 GetColor() { return m_Color; }
	Vector3 GetPosition() { return m_Position; }
	float GetEmissionStrength() { return m_emissionStrength; }

	bool intersect(Ray& ray, float t_min, float t_max, hit_record &rec) const
	{
		Vector3 oc = ray.origin() - m_Position;
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
				rec.normal = ((rec.p - m_Position) / radius);
				return true;
			}

			temp = (-b + sqrt(b*b - a*c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = ray.point_at_parameter(rec.t);
				rec.normal = ((rec.p - m_Position) / radius);
				return true;
			}
		}
		return false;
	}

private:
	Vector3 m_Color;
	Vector3 m_Position;
	float radius = 0.1;
	float m_emissionStrength;
};