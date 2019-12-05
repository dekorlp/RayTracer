#pragma once
#define MAX_RAY_DEPTH 5 

#include <cstdlib> 
#include <cstdio> 
#include <cmath> 
#include <fstream> 
#include <vector> 
#include <iostream> 
#include <algorithm>
#include <cassert> 

#include "Sphere.h"
#include "Vector3f.h"

float mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}


/*Vec3f trace(
	const Vec3f &rayorig,
	const Vec3f &raydir,
	const std::vector<IPrimitive*> &spheres,
	const int &depth)
{
	float tnear = INFINITY;
	const IPrimitive* prim = NULL;
	const IPrimitive* lightPrim = NULL;
	Vec3f pixelColor = 0;

	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i) {
		float distance = INFINITY;
		if (spheres[i]->intersect(rayorig, raydir, distance)) {
			//select primitive with nearest distance
			if (distance < tnear ) {
				// normal primitive
				tnear = distance;
				prim = &*spheres[i];
			}
		}
	}

	if (prim)
	{
		// primitive found
		Vec3f phit = rayorig + raydir * tnear; // point of intersection 
		Vec3f nhit = phit - prim->center; // normal at the intersection point
		nhit.normalize();

		if (raydir.dot(nhit) > 0) nhit = -nhit;

		if (prim->reflection > 0 && depth < MAX_RAY_DEPTH) {
			float facingratio = -raydir.dot(nhit);
			// change the mix value to tweak the effect
			float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);

			Vec3f refldir = raydir - nhit * 2 * raydir.dot(nhit);
			refldir.normalize();
			Vec3f reflection = trace(phit + nhit, refldir, spheres, depth + 1);


			pixelColor = (
			reflection * fresneleffect + (1 - fresneleffect) * prim->transparency) * prim->surfaceColor;

		}

		pixelColor = pixelColor + prim->emissionColor;

		
	}
	else
	{
		pixelColor = Vec3f(1, 1, 1);
		// primitive not found
	}

	return pixelColor;
}*/

