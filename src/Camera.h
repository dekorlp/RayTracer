#pragma once

#include "Vector3.h"
#include "Ray.h"


class Camera
{
public:
	Camera(Vector3& position, Vector3& lookAt, Vector3& up, float vfov, float aspect, float width, float height)
	{
		float scale = tan(deg2rad(vfov * 0.5));
		mCamera = Matrix::Camera(position, lookAt, up);

		mAspectRatio = aspect;
		mScale = scale;
		mWith = width;
		mHeight = height;
		mOrigin = position;

	}

	double deg2rad(double degrees) {
		return degrees * 4.0 * atan(1.0) / 180.0;
	}

	Ray getRay(float i, float j)
	{
		float x = (2 * (i + 0.5) / float(mWith) - 1) * mAspectRatio *  mScale;
		float y = (1 - 2 * (j + 0.5) / float(mHeight) * mScale);

		Vector3 dir = mCamera.multiply(1, Vector3(x, y, -1));
		return Ray(mOrigin, dir);
	}
private:

	float mWith;
	float mHeight;
	Vector3 mOrigin;
	Matrix mCamera;
	float mAspectRatio;
	float mScale;
};