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

std::shared_ptr<Ray> RayTraceCamera::VwToRay(double v, double w)
{
	return std::make_shared<Ray>( m_CamPosition, m_CamDirection + m_EV * v + m_EW * w);
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

Color RayTraceCamera::ColorAt(double v, double w)
{
	auto ray = VwToRay(v, w);
	std::shared_ptr<PointOnPrimitive> p = m_Scene.RayTrace(ray);
	if (p == nullptr)
		return m_Scene.GetBackground();
	else
	{
		/*Ray rayToSun = std::make_shared<Ray>(p->ToPointInSpace() + m_Scene.GetDirectionToSun() * minDistToRayStart, m_Scene.GetDirectionToSun);
		if (m_Scene.RayTraceHits(rayToSun)) return AdjustColor(p->GetColor(), m_Scene.GetMaxDarkening);

		Vector3 n = p->GetNormal();
		if (n == Vector3(0,0,0)) return p->GetColor();

		if (ray->GetDirection() * n > Vector3(0, 0, 0)) n = Vector3::Opposite(n);

		double brightness;
		double cosAngleToLight =  m_Scene.GetDirectionToSun().dot(n);

		if (cosAngleToLight > 0)
			brightness = m_Scene.GetMaxDarkening() + (m_Scene.GetMaxLightening() - m_Scene.GetMaxDarkening()) * cosAngleToLight;
		else
			brightness = m_Scene.GetMaxDarkening();

		return AdjustColor(p->GetColor(), brightness);*/
	}
}

wxBitmap RayTraceCamera::RenderBitmap()
{
	int centerV = m_ScreenWidthPx / 2;
	int centerW = m_ScreenHeightPx / 2;
	return nullptr;
}