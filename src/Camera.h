#pragma once

#include "Vector3.h"
#include "Ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Camera
{
public:
	Camera(Vector3 position, Vector3 lookAt, Vector3 up, float vfov, float aspect)
	{
		Vector3 u, v, w;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = position;
		w = unit_vector(position - lookAt);
		u = unit_vector(cross(up, w));
		v = cross(w, u);
		//lower_left_corner = Vector3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width * u - half_height*v - w;
		horizontal = 2 * half_width*u;
		vertical = 2 * half_height*v;
	}

	Ray getRay(float u, float v)
	{
		return Ray(origin, lower_left_corner + u* horizontal + v*vertical - origin);
	}
private:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;
};