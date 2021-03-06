#include "Scene.h"

unsigned int Scene::Add(IPrimitive *primitive)
{
	mPrimitives.push_back(primitive);
	return mPrimitives.size()-1;
}

Plane Scene::AddPlane(Vector3& position, float width, float height, Vector3& surfaceColor, float reflection)
{

	Vector3 leftSide = Vector3(position.x() - width / 2, position.y() - height / 2, position.z());
	Vector3 rightSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
	Vector3 leftSideTop = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
	Vector3 rightSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z());
	unsigned int index1 = this->Add(new Triangle(leftSide, leftSideTop, rightSideTop, surfaceColor, reflection));
	unsigned int index2 = this->Add(new Triangle(rightSideTop, rightSide, leftSide, surfaceColor, reflection));

	return Plane({ index1, index2 }, &mPrimitives);
}

Plane Scene::AddPlanePBR(Vector3& position, float width, float height, Vector3& surfaceColor, float metallic, float roughness, float ambientOcclusion)
{
	Vector3 leftSide = Vector3(position.x() - width / 2, position.y() - height / 2, position.z());
	Vector3 rightSide = Vector3(position.x() + width / 2, position.y() - height / 2, position.z());
	Vector3 leftSideTop = Vector3(position.x() - width / 2, position.y() + height / 2, position.z());
	Vector3 rightSideTop = Vector3(position.x() + width / 2, position.y() + height / 2, position.z());


	unsigned int index1 = this->Add(new TrianglePBR(leftSide, leftSideTop, rightSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
	unsigned int index2 = this->Add(new TrianglePBR(rightSideTop, rightSide, leftSide, surfaceColor, metallic, roughness, ambientOcclusion));
	
	return Plane({index1, index2}, &mPrimitives);
}

void Scene::AddCube(Vector3& position, float width, float height, float depth, Vector3& surfaceColor, float metallic, float roughness, float ambientOcclusion)
{

	Vector3 point1 = Vector3(-1.0f, -1.0f, -1.0f); // triangle 1 : begin
	Vector3 point2 = Vector3(-1.0f, -1.0f, 1.0f);
	Vector3 point3 = Vector3(-1.0f, 1.0f, 1.0f); // triangle 1 : end
	Vector3 point4 = Vector3(1.0f, 1.0f, -1.0f); // triangle 2 : begin
	Vector3 point5 = Vector3(-1.0f, -1.0f, -1.0f);
	Vector3 point6 = Vector3(-1.0f, 1.0f, -1.0f); // triangle 2 : end
	Vector3 point7 = Vector3(1.0f, -1.0f, 1.0f);
	Vector3 point8 = Vector3(-1.0f, -1.0f, -1.0f);
	Vector3 point9 = Vector3(1.0f, -1.0f, -1.0f);
	Vector3 point10 = Vector3(1.0f, 1.0f, -1.0f);
	Vector3 point11 = Vector3(1.0f, -1.0f, -1.0f);
	Vector3 point12 = Vector3(-1.0f, -1.0f, -1.0f);
	Vector3 point13 = Vector3(-1.0f, -1.0f, -1.0);
	Vector3 point14 = Vector3(-1.0f, 1.0f, 1.0f);
	Vector3 point15 = Vector3(-1.0f, 1.0f, -1.0f);
	Vector3 point16 = Vector3(1.0f, -1.0f, 1.0f);
	Vector3 point17 = Vector3(-1.0f, -1.0f, 1.0f);
	Vector3 point18 = Vector3(-1.0f, -1.0f, -1.0f);
	Vector3 point19 = Vector3(-1.0f, 1.0f, 1.0f);
	Vector3 point20 = Vector3(-1.0f, -1.0f, 1.0f);
	Vector3 point21 = Vector3(1.0f, -1.0f, 1.0f);
	Vector3 point22 = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 point23 = Vector3(1.0f, -1.0f, -1.0f);
	Vector3 point24 = Vector3(1.0f, 1.0f, -1.0f);
	Vector3 point25 = Vector3(1.0f, -1.0f, -1.0f);
	Vector3 point26 = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 point27 = Vector3(1.0f, -1.0f, 1.0f);
	Vector3 point28 = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 point29 = Vector3(1.0f, 1.0f, -1.0f);
	Vector3 point30 = Vector3(-1.0f, 1.0f, -1.0f);
	Vector3 point31 = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 point32 = Vector3(-1.0f, 1.0f, -1.0f);
	Vector3 point33 = Vector3(-1.0f, 1.0f, 1.0f);
	Vector3 point34 = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 point35 = Vector3(-1.0f, 1.0f, 1.0f);
	Vector3 point36 = Vector3(1.0f, -1.0f, 1.0f);

	this->Add(new TrianglePBR(point1, point2, point3, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point4, point5, point6, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point7, point8, point9, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point10, point11, point12, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point13, point14, point15, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point16, point17, point18, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point19, point20, point21, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point22, point23, point24, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point25, point26, point27, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point28, point29, point30, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point31, point32, point33, surfaceColor, metallic, roughness, ambientOcclusion));
	this->Add(new TrianglePBR(point34, point35, point36, surfaceColor, metallic, roughness, ambientOcclusion));

	/*// top plane
	{
		Vector3 leftSide = Vector3(position.x() - width / 2, position.y() - depth / 2, position.z() + height / 2);
		Vector3 rightSide = Vector3(position.x() + width / 2, position.y() - depth / 2, position.z() + height / 2);
		Vector3 leftSideTop = Vector3(position.x() - width / 2, position.y() + depth / 2, position.z() + height / 2);
		Vector3 rightSideTop = Vector3(position.x() + width / 2, position.y() + depth / 2, position.z() + height / 2);



		unsigned int index1 = this->Add(new TrianglePBR(leftSide, leftSideTop, rightSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
		unsigned int index2 = this->Add(new TrianglePBR(rightSideTop, rightSide, leftSide, surfaceColor, metallic, roughness, ambientOcclusion));
	}

	// bottom plane
	{
		Vector3 leftSide = Vector3(position.x() - width / 2, position.y() - depth / 2, position.z() - height / 2);
		Vector3 rightSide = Vector3(position.x() + width / 2, position.y() - depth / 2, position.z() - height / 2);
		Vector3 leftSideTop = Vector3(position.x() - width / 2, position.y() + depth / 2, position.z() - height / 2);
		Vector3 rightSideTop = Vector3(position.x() + width / 2, position.y() + depth / 2, position.z() - height /2 );


		unsigned int index1 = this->Add(new TrianglePBR(leftSide, leftSideTop, rightSideTop, surfaceColor, metallic, roughness, ambientOcclusion));
		unsigned int index2 = this->Add(new TrianglePBR(rightSideTop, rightSide, leftSide, surfaceColor, metallic, roughness, ambientOcclusion));
	}

	// right plane
	{
		Vector3 leftSideRIGHT = Vector3(position.x() - width / 2, position.y() - depth / 2, position.z() - height / 2);
		Vector3 rightSideRIGHT = Vector3(position.x() - width / 2, position.y() + depth / 2, position.z() - height / 2);
		Vector3 leftSideTopRIGHT = Vector3(position.x() - width / 2, position.y() - depth / 2, position.z() + height / 2);
		Vector3 rightSideTopRIGHT = Vector3(position.x() - width / 2, position.y() + depth / 2, position.z() + height / 2);


		unsigned int index1 = this->Add(new TrianglePBR(leftSideRIGHT, leftSideTopRIGHT, rightSideTopRIGHT, surfaceColor, metallic, roughness, ambientOcclusion));
		unsigned int index2 = this->Add(new TrianglePBR(rightSideTopRIGHT, rightSideRIGHT, leftSideRIGHT, surfaceColor, metallic, roughness, ambientOcclusion));
	}*/

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
	Vector3 norm = rec.normal;

	// diffuse component (nochmal kontrollieren, Normale <-> Position))
	
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

		float spec = std::pow(std::max(dot(viewDir, -reflectDir), 0.0f), 32);
		specular = (specularStrength * spec * mLight->GetColor());
	}


	// specular component (=+ vermutlich += nochmal pr�fen)
	// primitives
	Vector3 specPrim = Vector3(0, 0, 0);
#ifdef USE_REFLECTION
	if (depth < 1 && specularStrength > 0)
	{
		// other primitives
		Vector3 R = unit_vector(Reflect(r.direction(), norm));
		Vector3 Col = Trace(Ray(rec.p + norm, R), depth + 1);

		specPrim = specularStrength * Col;
	}
#endif

	Vector3 result = (ambient + diffuse + (specular + specPrim )/2 ) * mPrimitives[primitiveIndex]->surfaceColor;
	return result;
}



Vector3 Scene::PBRShading(Ray &r, hit_record& rec, int depth, unsigned int primitiveIndex)
{
	Vector3 albedo = mPrimitives[primitiveIndex]->surfaceColor;
	float metallic = mPrimitives[primitiveIndex]->mMetallic;
	float roughness = mPrimitives[primitiveIndex]->mRroughness;
	float ao = mPrimitives[primitiveIndex]->mAmbientOcclusion;

	Vector3 norm = rec.normal;

	Vector3 lightDir = unit_vector(mLight->GetPosition() - rec.p);

	// render PBR Diffusion and Specular Component
	
	Vector3 viewDir = unit_vector(r.origin() - rec.p);
	Vector3 h = (unit_vector(lightDir + viewDir));
	Vector3 F0 = Vector3(0.04, 0.04, 0.04);
	Vector3 Lo = Vector3(0.0, 0.0, 0.0);

	float distance = (mLight->GetPosition() - rec.p).length();
	float attenuation = 1.0 / distance * distance;
	Vector3 radiance = mLight->GetColor() * attenuation;

	F0 = Lerp(F0, albedo, metallic);

	float NDF = PhysicalBasedShading::TrowbridgeReitzDistributionGGX(h, norm, roughness);
	float G = PhysicalBasedShading::GeometrySchlickGGX(norm, viewDir, roughness);
	Vector3 F = PhysicalBasedShading::FresnelSchlick(viewDir, h, F0);

	Vector3 numerator = NDF * G * F;
	float denominator = 4.0 * std::max(dot(norm, lightDir), 0.0f) * std::max(dot(norm, viewDir), 0.0f);

	Vector3 specular = numerator / std::max(denominator, 0.001f);
	
	// reflection component
	// primitives
	Vector3 reflection = Vector3(0, 0, 0);
#ifdef USE_REFLECTION
	if (depth < MAX_RAY_DEPTH && metallic > 0)
	{
		// other primitives
		Vector3 R = unit_vector(Reflect(r.direction(), norm));
		Vector3 Col = Trace(Ray(rec.p + norm , R), depth + 1);

		reflection = metallic * Col ;
	}
#endif

	Vector3 kS = F;
	Vector3 kD = Vector3(1.0, 1.0, 1.0) - kS;
	kD *= 1.0 - metallic;
	float NdotL = std::max(dot(norm, lightDir), 0.0f);
	Lo += (albedo / PI + specular) * radiance * NdotL;

	Vector3 ambient = Vector3(0.3, 0.3, 0.3) * albedo * ao;
	Vector3 color = ambient + ((Lo + reflection)/2);
	
	return color;
}

Vector3 Scene::Trace(Ray& r, int depth )
{
	for (unsigned int i = 0; i < mPrimitives.size(); i++)
	{
		hit_record rec;
		if (mPrimitives[i]->intersect(r, 0.001f, std::numeric_limits<float>::max(), rec))
		{
			Vector3 lightDir = mLight->GetPosition() - rec.p;
			Vector3 lightDirNorm = unit_vector(lightDir);
			double maxDistance = lightDir.length();

			Ray shadowRay(rec.p + rec.normal * 0.001f, lightDirNorm);
			bool isShadow = false;
			for (int j = 0; j < mPrimitives.size(); j++)
			{
				hit_record shadowHit;
				if (mPrimitives[j]->intersect(shadowRay, 0.001f, std::numeric_limits<float>::max(), shadowHit))
				{
					Vector3 shadowHitLigthDit = shadowHit.p - rec.p;
					double distanceShadowHit = shadowHitLigthDit.length();
					if (maxDistance > distanceShadowHit)
					{

						isShadow = true;
						break;
					}
				}
			}
#ifdef USE_SHADOW
			if (!isShadow)
			{
#endif
#ifdef PHONG_SHADING
				return PhongShading(r, rec, depth, i);
#endif

#ifdef PBR_SHADING
				return PBRShading(r, rec, depth, i);
#endif

#ifdef USE_SHADOW
			}
			else
			{
				Vector3 ambient = Vector3(0.05, 0.05, 0.05);
				return ambient * mPrimitives[i]->surfaceColor;
			}
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