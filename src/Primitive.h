#pragma once
#include "Color.h"
#include "Ray.h"

class Primitive {
private:
	Color m_Color;
	
public:
	//PointOnPrimitive RayTrace();
	
	Primitive(Color color);

};