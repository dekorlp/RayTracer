#include "Scene.h"

void Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
}

void Scene::AddPlane(Vector3 position, float width, float height, Vector3 surfaceColor, float reflection)
{

	Vector3 leftSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
	Vector3 rightSide = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
	Vector3 leftSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z() );
	Vector3 rightSideTop = Vector3(position.x() - width / 2, position.y() - height / 2, position.z() );
	this->Add(new Triangle(leftSide, rightSide, leftSideTop, surfaceColor, reflection));
	this->Add(new Triangle(leftSide, rightSide, rightSideTop, surfaceColor, reflection));

}

void Scene::Add(Light *light)
{
	mLight = light;
}

Vector3 Scene::Trace(Ray& r, int depth )
{
	for (int i = 0; i < mPrimitives.size(); i++)
	{
		hit_record rec;
		if (mPrimitives[i]->intersect(r, 0.001, std::numeric_limits<float>::max(), rec))
		{
			// ambient component
			float ambientStrength = 0.18;
			Vector3 ambient = ambientStrength *mLight->GetColor();
			
			
			
			Vector3 lightDir = unit_vector(mLight->GetPosition() - rec.p);

			// render Shadow
			hit_record shadow_rec;
			for (int j = 0; j < mPrimitives.size(); j++)
			{

				if (mPrimitives[j]->intersect(Ray(rec.p, -lightDir), 0.001, std::numeric_limits<float>::max(), shadow_rec))
				{
					return ambient * Vector3(0.098,0.098,0.098);
				}
			}

			// diffuse component (nochmal kontrollieren, Normale <-> Position))
			Vector3 norm = -rec.normal;
			float diff = std::max(dot(norm, lightDir), 0.0f);
			Vector3 diffuse = diff *  mLight->GetColor();
	
			// specular component
			// light
			float specularStrength = mPrimitives[i]->mReflection;

			Vector3 specular = Vector3(0, 0, 0);
			if (specularStrength > 0)
			{
				Vector3 viewDir = unit_vector(r.origin() - rec.p);
				Vector3 reflectDir = unit_vector(Reflect(lightDir, norm)); // lightDir - norm * 2 * dot(lightDir, norm);
				//if(dot(lightDir, norm))

				float spec = std::pow(std::max(dot(viewDir, reflectDir), 0.0f), 32);
				specular = (specularStrength * spec * mLight->GetColor());
			}
			
			// specular component (=+ vermutlich += nochmal prüfen)
			// primitives
			Vector3 specPrim = Vector3(0, 0, 0);

			if (depth < MAX_RAY_DEPTH && specularStrength > 0)
			{
				// other primitives
				Vector3 R = unit_vector(Reflect(r.direction(), rec.normal));
				Vector3 Col = Trace(Ray(rec.p + rec.normal, R), depth + 1);

				specPrim = specularStrength * Col;
			}

			Vector3 result = ( ambient + diffuse + (specular + specPrim) / 2) * mPrimitives[i]->surfaceColor;
			return result;
		}
	}
	// extra for global lightning
	//Vector3 unit_direction = unit_vector(r.direction());
	//float t = 0.5 * (unit_direction.y() + 1.0);
	//return (1.0 - t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
	return Vector3(176.0 / 255.0, 224.0 / 255.0, 230.0 / 255.0);

	/*if (!objectFound && depth == 0)
	{
		Vector3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
	}
	else
	{
		return Vector3(0, 0, 0);
	}*/

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