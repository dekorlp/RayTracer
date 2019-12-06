#include "Vector3.h"

std::istream& operator>> (std::istream &is, Vector3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

std::ostream& operator<<(std::ostream &os, const Vector3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

void Vector3::make_unit_vector()
{
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

 Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

Vector3 operator/(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

Vector3 operator*(float t, const Vector3 &v)
{
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

Vector3 operator/(const Vector3 &v, float t)
{
	return Vector3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

Vector3 operator*( const Vector3 &v, float t)
{
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

float dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

Vector3 cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

Vector3& Vector3::operator+=(const Vector3 &v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

Vector3& Vector3::operator*=(const Vector3 &v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

Vector3& Vector3::operator/=(const Vector3 &v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

Vector3& Vector3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

Vector3& Vector3::operator/=(const float t)
{
	float k = 1.0 / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

Vector3 unit_vector(Vector3 v)
{
	return v / v.length();
}