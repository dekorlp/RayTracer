#include "PointOnPrimitive.h"

double PointOnPrimitive::GetDistanceToRayStart()
{
	return m_DistanceToRayStart;
}


PointOnPrimitive::PointOnPrimitive(double distanceToRayStart)
{
	m_DistanceToRayStart = distanceToRayStart;
}