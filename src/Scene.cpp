#include "Scene.h"

void Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
}

void Scene::Add(Light *light)
{
	mLight = light;
}

Vector3 Scene::Trace(Ray& r, int depth)
{
	for (int i = 0; i < mPrimitives.size(); i++)
	{
		hit_record rec;
		if (mPrimitives[i]->intersect(r, 0.0, std::numeric_limits<float>::max(), rec))
		{
			Vector3 finalColor = mPrimitives[i]->surfaceColor;

			// ambient component
			float ambientStrength = 0.1;
			Vector3 ambient = ambientStrength *mLight->GetColor();

			// diffuse component
			Vector3 norm = rec.normal;
			Vector3 lightDir = unit_vector(mLight->GetPosition() - norm);
			float diff = std::max(dot(norm, lightDir), 0.0f);
			Vector3 diffuse = diff * mLight->GetColor();

			// specular component
			// light
			float specularStrength = 0.9;
			Vector3 viewDir = unit_vector(r.origin() - rec.p);
			Vector3 reflectDir = lightDir - norm * 2 * dot(lightDir, norm);

			float spec = std::pow(std::max(dot(viewDir, reflectDir), 0.0f), 32);
			Vector3 specular = specularStrength * spec * mLight->GetColor();
			
			Vector3 specPrim = Vector3(0, 0, 0);
			// specular primitives
			if (depth < MAX_RAY_DEPTH)
			{
				// other primitives
				Vector3 R = Reflect(r.direction(), rec.normal);
				Vector3 Col =+ Trace(Ray(rec.p + rec.normal, R), depth +1);
				specPrim =+ specularStrength * (Col + specular);	
			}

			Vector3 result = (ambient + diffuse + (specPrim + specular)) * finalColor;
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