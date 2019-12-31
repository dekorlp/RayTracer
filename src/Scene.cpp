#include "Scene.h"

unsigned int Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
	return mPrimitives.size()-1;
}

Plane Scene::AddPlane(Vector3& position, float width, float height, Vector3& surfaceColor, float reflection)
{

	Vector3 leftSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
	Vector3 rightSide = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
	Vector3 leftSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z() );
	Vector3 rightSideTop = Vector3(position.x() - width / 2, position.y() - height / 2, position.z() );
	unsigned int index1 = this->Add(new Triangle(leftSide, rightSide, leftSideTop, surfaceColor, reflection));
	unsigned int index2 = this->Add(new Triangle(leftSide, rightSide, rightSideTop, surfaceColor, reflection));

	return Plane({ index1, index2 }, &mPrimitives);
}

Plane Scene::AddPlanePBR(Vector3& position, float width, float height, Vector3& surfaceColor, float metallic, float roughness, float ambientOcclusion)
{
	Vector3 leftSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
	Vector3 rightSide = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
	Vector3 leftSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z());
	Vector3 rightSideTop = Vector3(position.x() - width / 2, position.y() - height / 2, position.z());
	unsigned int index1 = this->Add(new TrianglePBR(leftSide, rightSide, leftSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
	unsigned int index2 = this->Add(new TrianglePBR(leftSide, rightSide, rightSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
	
	return Plane({index1, index2}, &mPrimitives);
}

void Scene::AddCube(Vector3& position, float width, float height, float depth, Vector3& surfaceColor, float metallic, float roughness, float ambientOcclusion)
{
	// funktioniert noch nicht

	{
		// bottom side
		Vector3 leftSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
		Vector3 rightSide = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
		Vector3 leftSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z());
		Vector3 rightSideTop = Vector3(position.x() - width / 2, position.y() - height / 2, position.z());
		unsigned int index1 = this->Add(new TrianglePBR(leftSide, rightSide, leftSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
		unsigned int index2 = this->Add(new TrianglePBR(leftSide, rightSide, rightSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
	}

}

void Scene::AddTriangleList(std::vector<Triangle> triangleList)
{
	for (int i = 0; i < triangleList.size(); i++)
	{
		Triangle *triangle = new Triangle(triangleList[i]);
		this->Add(triangle);
	}
}

void Scene::Add(Light *light)
{
	mLight = light;
}

Vector3 Scene::Reflect(const Vector3& v, const Vector3& n)
{
	return v - 2 * dot(v, n)*n;
}

Vector3 Scene::Lerp(const Vector3&a, const Vector3&b, const float& t)
{
	return (1.0f - t)* a + t*b;
}

Vector3 Scene::PhongShading(Ray &r, hit_record& rec, int depth, unsigned int primitiveIndex)
{
	// ambient component
	float ambientStrength = 0.18f;
	Vector3 ambient = ambientStrength *mLight->GetColor();



	Vector3 lightDir = unit_vector(mLight->GetPosition() - rec.p);

	// render Shadow
	hit_record shadow_rec;
	for (unsigned int j = 0; j < mPrimitives.size(); j++)
	{

		if (mPrimitives[j]->intersect(Ray(rec.p, -lightDir), 0.001f, std::numeric_limits<float>::max(), shadow_rec)
			&& depth == 0
			&& dot(rec.p + rec.normal, lightDir) > 0.15) // 0.15 creates in my opinion the best shadow style
		{
			return ambient * Vector3(0.098f, 0.098f, 0.098f);
		}
	}

	// diffuse component (nochmal kontrollieren, Normale <-> Position))
	Vector3 norm = -rec.normal;
	float diff = std::max(dot(norm, lightDir), 0.0f);
	Vector3 diffuse = diff *  mLight->GetColor();

	// specular component
	// light
	float specularStrength = mPrimitives[primitiveIndex]->mReflection;

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

	Vector3 result = (ambient + diffuse + (specular + specPrim) / 2) * mPrimitives[primitiveIndex]->surfaceColor;
	return result;
}



Vector3 Scene::PBRShading(Ray &r, hit_record& rec, int depth, unsigned int primitiveIndex)
{
	Vector3 albedo = mPrimitives[primitiveIndex]->surfaceColor;
	float metallic = mPrimitives[primitiveIndex]->mMetallic;
	float roughness = mPrimitives[primitiveIndex]->mRroughness;
	float ao = mPrimitives[primitiveIndex]->mAmbientOcclusion;
	float emmissionStrength = mLight->GetEmissionStrength();

	Vector3 lightDir = unit_vector(mLight->GetPosition() - rec.p);

	// render Shadow
	hit_record shadow_rec;
	for (unsigned int j = 0; j < mPrimitives.size(); j++)
	{

		if (mPrimitives[j]->intersect(Ray(rec.p, -lightDir), 0.001f, std::numeric_limits<float>::max(), shadow_rec)
			&& depth == 0
			&& dot(rec.p + rec.normal, lightDir) > 0.15) // 0.15 creates in my opinion the best shadow style
		{
			return ao * Vector3(0.098f, 0.098f, 0.098f);
		}
	}

	// render PBR Diffusion and Specular Component
	Vector3 norm = rec.normal;
	Vector3 viewDir = unit_vector(r.origin() - rec.p);
	Vector3 h = (unit_vector(lightDir + viewDir));
	Vector3 F0 = Vector3(0.02, 0.02, 0.02);
	Vector3 Lo = Vector3(0.0, 0.0, 0.0);

	float distance = (mLight->GetPosition() - rec.p).length();
	float attenuation = 1.0 / (pow(distance, emmissionStrength));
	Vector3 radiance = mLight->GetColor() * attenuation;

	F0 = Lerp(F0, albedo, metallic);

	float NDF = PhysicalBasedShading::TrowbridgeReitzDistributionGGX(h, norm, roughness);
	float G = PhysicalBasedShading::GeometrySchlickGGX(norm, viewDir, roughness);
	Vector3 F = PhysicalBasedShading::FresnelSchlick(viewDir, h, F0);

	Vector3 numerator = G * F;
	float denominator = 4.0 * std::max(dot(-norm, lightDir), 0.0f) * std::max(dot(-norm, viewDir), 0.0f);

	Vector3 specular = numerator / std::max(denominator, 0.001f);
	
	// reflection component
	// primitives
	Vector3 reflection = Vector3(0, 0, 0);

	if (depth < MAX_RAY_DEPTH && metallic > 0)
	{
		// other primitives
		Vector3 R = unit_vector(Reflect(r.direction(), rec.normal));
		Vector3 Col = Trace(Ray(rec.p + rec.normal, R), depth + 1);

		reflection = metallic * Col;
	}

	Vector3 kS = F;
	Vector3 kD = Vector3(1.0, 1.0, 1.0) - kS;
	kD *= 1.0 - metallic;
	float NdotL = std::max(dot(-norm, lightDir), 0.0f);
	Lo += (kD * albedo / PI + specular) * radiance * NdotL;

	Vector3 ambient = Vector3(0.3, 0.3, 0.3) * albedo * ao;
	Vector3 color = ambient + (Lo + reflection)/2;

	
	return color ;
}

Vector3 Scene::Trace(Ray& r, int depth )
{
	for (unsigned int i = 0; i < mPrimitives.size(); i++)
	{
		hit_record rec;
		if (mPrimitives[i]->intersect(r, 0.001f, std::numeric_limits<float>::max(), rec))
		{
#ifdef PHONG_SHADING
			return PhongShading(r, rec, depth, i);
#endif

#ifdef PBR_SHADING
			return PBRShading(r, rec, depth, i);
#endif

		}
	}
	// extra for global lightning
	Vector3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return Lerp(Vector3(0.5, 0.7, 1.0), Vector3(1.0, 1.0, 1.0), t);
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