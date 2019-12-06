#pragma once
#include "Vector3.h"

class Light
{
public:
	Light(Vector3 color, Vector3 position) { m_Color = color; m_Position = position; }
	Vector3 GetColor() { return m_Color; }
	Vector3 GetPosition() { return m_Position; }
private:
	Vector3 m_Color;
	Vector3 m_Position;
};