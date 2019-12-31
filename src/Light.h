#pragma once
#include "Vector3.h"

class Light
{
public:
	Light(Vector3& color, Vector3& position, float emissionStrength) { m_Color = color; m_Position = position; m_emissionStrength = emissionStrength; }
	Vector3 GetColor() { return m_Color; }
	Vector3 GetPosition() { return m_Position; }
	float GetEmissionStrength() { return m_emissionStrength; }

private:
	Vector3 m_Color;
	Vector3 m_Position;
	float m_emissionStrength;
};