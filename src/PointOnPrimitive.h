#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Primitive.h"

class PointOnPrimitive
{
	private:
		double m_DistanceToRayStart;

	public:
		double GetDistanceToRayStart();

		virtual Vector3 ToPointInSpace() = 0;
		virtual Color GetColor() = 0;
		virtual Vector3 GetNormal() = 0;
		virtual Primitive GetPrimitive() = 0;

		PointOnPrimitive(double distanceToRayStart);
};