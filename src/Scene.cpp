#include "Scene.h"

void Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
}

void Scene::Add(Light *light)
{
	mLight = light;
}

Vector3 Scene::Trace(Ray& r)
{
	for (int i = 0; i < mPrimitives.size(); i++)
	{
		hit_record rec;
		if (mPrimitives[i]->intersect(r, 0.0, std::numeric_limits<float>::max(), rec))
		{
			// ambient component
			float ambientStrength = 0.5;
			Vector3 ambient = ambientStrength *mLight->GetColor();

			// diffuse component
			Vector3 norm = unit_vector(rec.normal);
			Vector3 lightDir = unit_vector(mLight->GetPosition() - rec.normal);
			float diff = std::max(dot(norm, lightDir), 0.0f);
			Vector3 diffuse = diff * mLight->GetColor();

			Vector3 result = (ambient + diffuse) * rec.color;
			return result;
		}
	}
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

Light* Scene::GetLight()
{
	return mLight;
}

void Scene::ClearPrimitives()
{
	mPrimitives.clear();
}

int Scene::PrimitiveCount()
{
	return mPrimitives.size();
}