#include "IRayTraceable.h"

void IRayTraceable::SetDirectionToSun(Vector3 directionToSun)
{
	m_DirectionToSun = directionToSun;
}

void IRayTraceable::SetBackground(Color background)
{
	m_Background = background;
}

void IRayTraceable::SetMaxLighening(double maxLightening)
{
	m_MaxLigthening = maxLightening;
}

void IRayTraceable::SetMaxDarkening(double maxDarkening)
{
	m_MaxDarkening = maxDarkening;
}

Vector3 IRayTraceable::GetDirectionToSun()
{
	return m_DirectionToSun;
}

Color IRayTraceable::GetBackground()
{
	return m_Background;
}

double IRayTraceable::GetMaxLightening()
{
	return m_MaxLigthening;
}

double IRayTraceable::GetMaxDarkening()
{
	return m_MaxDarkening;
}