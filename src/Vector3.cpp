#include "Vector3.h"

Vector3::Vector3()
{
	vec3.e = _mm_set_ps(0, 0, 0, 0);
}

Vector3::Vector3(float e0, float e1, float e2)
{
	vec3.e = _mm_set_ps(0, e2, e1, e0);
}

std::ostream& operator<<(std::ostream &os, const Vector3 &t)
{
	os << t.vec3.ef[0] << " " << t.vec3.ef[1] << " " << t.vec3.ef[2];
	return os;
}

std::istream& operator >> (std::istream &is, Vector3 &t)
{
	is >> t.vec3.ef[0] >> t.vec3.ef[1] >> t.vec3.ef[2];
	return is;
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{

	__m128 res = _mm_add_ps((__m128)v1.vec3.e, (__m128)v2.vec3.e);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{

	__m128 res = _mm_sub_ps((__m128)v1.vec3.e, (__m128)v2.vec3.e);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator/(const Vector3 &v1, const Vector3 &v2)
{
	__m128 res = _mm_div_ps((__m128)v1.vec3.e, (__m128)v2.vec3.e);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
{
	__m128 res = _mm_mul_ps((__m128)v1.vec3.e, (__m128)v2.vec3.e);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator*(const float &f, const Vector3 &v)
{
	__m128 constant = _mm_set_ps(0, f, f, f);
	__m128 res = _mm_mul_ps((__m128)v.vec3.e, (__m128)constant);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator*(const Vector3 &v, const float &f)
{
	__m128 constant = _mm_set_ps(0, f, f, f);
	__m128 res = _mm_mul_ps((__m128)v.vec3.e, (__m128)constant);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3 operator/(const Vector3 &v, const float &f)
{
	__m128 constant = _mm_set_ps(0, f, f, f);
	__m128 res = _mm_div_ps((__m128)v.vec3.e, (__m128)constant);
	return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
}

Vector3& Vector3::operator+=(const Vector3 &v)
{
	vec3.e = _mm_add_ps((__m128)vec3.e, (__m128)v.vec3.e);
	return *this;
}

Vector3& Vector3::operator*=(const Vector3 &v)
{
	vec3.e = _mm_mul_ps((__m128)vec3.e, (__m128)v.vec3.e);
	return *this;
}

Vector3& Vector3::operator/=(const Vector3 &v)
{
	vec3.e = _mm_div_ps((__m128)vec3.e, (__m128)v.vec3.e);
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &v)
{
	vec3.e = _mm_sub_ps((__m128)vec3.e, (__m128)v.vec3.e);
	return *this;
}

Vector3& Vector3::operator*=(const float f)
{
	__m128 constant = _mm_set_ps(0, f, f, f);
	vec3.e = _mm_mul_ps((__m128)vec3.e, (__m128)constant);
	return *this;
}

Vector3& Vector3::operator/=(const float f)
{
	__m128 constant = _mm_set_ps(0, f, f, f);
	vec3.e = _mm_div_ps((__m128)vec3.e, (__m128)constant);
	return *this;
}

void Vector3::make_unit_vector()
{
	float k = 1.0 / sqrt(vec3.e.m128_f32[0] * vec3.e.m128_f32[0] + vec3.e.m128_f32[1] * vec3.e.m128_f32[1] + vec3.e.m128_f32[2] * vec3.e.m128_f32[2]);
	vec3.ef[0] *= k; vec3.ef[1] *= k; vec3.ef[2] *= k;
}

float dot(const Vector3 &v1, const Vector3 &v2)
{

	return v1.vec3.e.m128_f32[0] * v2.vec3.e.m128_f32[0] + v1.vec3.e.m128_f32[1] * v2.vec3.e.m128_f32[1] + v1.vec3.e.m128_f32[2] * v2.vec3.e.m128_f32[2];
}

Vector3 cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3((v1.vec3.e.m128_f32[1] * v2.vec3.e.m128_f32[2] - v1.vec3.e.m128_f32[2] * v2.vec3.e.m128_f32[1]),
		(-(v1.vec3.e.m128_f32[0] * v2.vec3.e.m128_f32[2] - v1.vec3.e.m128_f32[2] * v2.vec3.e.m128_f32[0])),
		(v1.vec3.e.m128_f32[0] * v2.vec3.e.m128_f32[1] - v1.vec3.e.m128_f32[1] * v2.vec3.e.m128_f32[0]));
}

Vector3 unit_vector(Vector3 &v)
{
	return v / v.length();
}