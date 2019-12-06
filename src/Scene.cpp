#include "Scene.h"

void Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
}

Vector3 Scene::Trace(Ray& r)
{
	if (mPrimitives[2]->intersect(r))
		return Vector3(1, 0, 0);
	Vector3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
}

IPrimitive* Scene::getPrimitive(int index)
{
	return mPrimitives[index];
}

void Scene::DeletePrimitive(int index)
{
	mPrimitives.erase(mPrimitives.begin() + index);
}

void Scene::ClearPrimitives()
{
	mPrimitives.clear();
}

int Scene::PrimitiveCount()
{
	return mPrimitives.size();
}