#include "Ray.h"

Ray:: Ray(Vector3 &start, Vector3 &direction)
{
	this->m_Start = start;
	this->m_Direction = direction;
}

Vector3 Ray::GetStart()
{
	return m_Start;
}

Vector3 Ray::GetDirection()
{
	return m_Direction;
}