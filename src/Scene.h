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
#include <limits>

#include "Sphere.h"
#include "Light.h"
#include "Vector3.h"
#include "Triangle.h"
#include "Ray.h"

class Scene
{
	public:
		void Add(IPrimitive *primitive);
		void AddPlane(Vector3 position, float width, float height, Vector3 surfaceColor, float reflection = 0);
		void Add(Light *light);
		void DeletePrimitive(int index);
		int PrimitiveCount();
		IPrimitive* getPrimitive(int index);
		void ClearPrimitives();
		Light* GetLight();

		Vector3 Trace(Ray& r, int depth = 0);

	private:
		Vector3 Reflect(const Vector3& v, const Vector3& n);
		Vector3 Lerp(const Vector3&a, const Vector3&b, const float& t);
		std::vector<IPrimitive*> mPrimitives;
		Light* mLight;
};

