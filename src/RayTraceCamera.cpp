#include "RayTraceCamera.h"


RayTraceCamera::RayTraceCamera(IRayTraceable& scene, Vector3& camPosition, Vector3& camDirection) : m_Scene(scene),
m_CamPosition(camPosition), m_CamDirection(camDirection)
{
	m_UpDirection = Vector3(0, 1, 0);
	MoveTo(camPosition, camDirection);
}

void RayTraceCamera::MoveTo(Vector3& position, Vector3& direction, Vector3& upDirection)
{
	if (upDirection != Vector3(0, 0, 0)) this->m_UpDirection = Vector3::Normalize(upDirection);
	m_CamPosition = position;
	m_CamDirectionNorm = Vector3::Normalize(direction);
	m_CamDirection = direction;
	Init();
}

void RayTraceCamera::ResizeScreen(int widthPx, int heightPx)
{
	m_ScreenWidthPx = widthPx;
	m_ScreenHeightPx = heightPx;
	Init();
}

void RayTraceCamera::Init()
{
	m_EV = m_CamDirectionNorm.cross(m_UpDirection);
	m_EW = m_EV.cross(m_CamDirectionNorm);
	m_EV = m_EV * (m_ScreenWidth / m_ScreenWidthPx);
	m_EW = m_EW * (m_ScreenWidth / m_ScreenHeightPx);
}

Ray* RayTraceCamera::VwToRay(double v, double w)
{
	return new Ray(m_CamPosition, m_CamDirection + m_EV * v + m_EW * w);
}

Color RayTraceCamera::AdjustColor(Color c, double brightness)
{
	if (brightness == 0)
		return Color( // Die Farbe aufhellen
			(int)((255 - c.GetRComponent()) * brightness),
			(int)((255 - c.GetGComponent()) * brightness),
			(int)((255 - c.GetBComponent()) * brightness)
		);
	else // if brightness &lt; 0
		return Color( // Die Farbe abdunkeln
			(int)(c.GetRComponent() * (1 + brightness)),
			(int)(c.GetGComponent() * (1 + brightness)),
			(int)(c.GetBComponent() * (1 + brightness))
		);
}