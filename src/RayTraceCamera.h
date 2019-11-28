#pragma once

#include "IRayTraceable.h"
#include "Vector3.h"
#include "Ray.h"

class RayTraceCamera
{
private:
	IRayTraceable &m_Scene;
	Vector3 m_CamPosition;
	Vector3 m_CamDirection;
	Vector3 m_CamDirectionNorm;
	Vector3 m_UpDirection;

	const double m_EyeDistanceToScreen = 1.5;
	const double m_ScreenWidth = 1;
	Vector3 m_EV;
	Vector3 m_EW;

	int m_ScreenWidthPx = 300;
	int m_ScreenHeightPx = 200;

public:
	RayTraceCamera(IRayTraceable& scene, Vector3& camPosition, Vector3& camDirection);

	void MoveTo(Vector3& position, Vector3& direction, Vector3& upDirection = Vector3(0, 0, 0));

	void ResizeScreen(int widthPx, int heightPx);

	void Init();

	Ray* VwToRay(double v, double w);

	static Color AdjustColor(Color c, double brightness);
};