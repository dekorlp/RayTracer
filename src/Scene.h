#pragma once
#define MAX_RAY_DEPTH 5 
# define PI           3.14159265358979323846  /* pi */

#include <cstdlib> 
#include <cstdio> 
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
#include "PhysicalBasedShading.h"

class Scene
{
	public:
		void Add(IPrimitive *primitive);
		void AddTriangleList(std::vector<Triangle> triangleList);
		void AddPlane(Vector3& position, float width, float height, Vector3& surfaceColor, float reflection = 0);
		void Add(Light *light);
		void DeletePrimitive(int index);
		int PrimitiveCount();
		IPrimitive* getPrimitive(int index);
		void ClearPrimitives();
		Light* GetLight();
		Vector3 PhongShading(Ray &r, hit_record& rec, int depth, unsigned int primitiveIndex);
		Vector3 PBRShading(Ray &r, hit_record& rec, int depth, unsigned int primitiveIndex);

		Vector3 Trace(Ray& r, int depth = 0);

	private:
		Vector3 Reflect(const Vector3& v, const Vector3& n);
		Vector3 Lerp(const Vector3&a, const Vector3&b, const float& t);
		std::vector<IPrimitive*> mPrimitives;
		Light* mLight;
};

