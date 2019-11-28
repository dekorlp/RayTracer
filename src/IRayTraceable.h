#pragma once

#include "Vector3.h"
#include "Color.h"
#include "PointOnPrimitive.h"
#include "Ray.h"

class IRayTraceable
{
private:
	Vector3 m_DirectionToSun;
	Color m_Background;
	double m_MaxLigthening;
	double m_MaxDarkening;
public:
	
	void SetDirectionToSun(Vector3 directionToSun);
	void SetBackground(Color background);
	void SetMaxLighening(double maxLightening);
	void SetMaxDarkening(double maxDarkening);
	
	Vector3 GetDirectionToSun();
	Color GetBackground();
	double GetMaxLightening();
	double GetMaxDarkening();

	virtual PointOnPrimitive RayTrace(Ray ray) = 0;
	virtual bool RayTraceHits(Ray ray) = 0;
};