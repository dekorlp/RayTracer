#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

#define __SSE__

#if (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64)) && ! defined(__x86_64__)
#define __x86_64__ 1
#endif

#ifndef SSE_INSTR_SET
#if defined ( __AVX2__ )
#define SSE_INSTR_SET 8
#elif defined ( __AVX__ )
#define SSE_INSTR_SET 7
#elif defined ( __SSE4_2__ )
#define SSE_INSTR_SET 6
#elif defined ( __SSE4_1__ )
#define SSE_INSTR_SET 5
#elif defined ( __SSSE3__ )
#define SSE_INSTR_SET 4
#elif defined ( __SSE3__ )
#define SSE_INSTR_SET 3
#elif defined ( __SSE2__ ) || defined ( __x86_64__ )
#define SSE_INSTR_SET 2
#elif defined ( __SSE__ )
#define SSE_INSTR_SET 1
#elif defined ( _M_IX86_FP )           // Defined in MS compiler on 32bits system. 1: SSE, 2: SSE2
#define SSE_INSTR_SET _M_IX86_FP
#else
#define SSE_INSTR_SET 0
#endif // instruction set defines
#endif // SSE_INSTR_SET

#if SSE_INSTR_SET > 7                  // AVX2 and later
#ifdef __GNUC__
#include <x86intrin.h>         // x86intrin.h includes header files for whatever instruction
// sets are specified on the compiler command line, such as:
// xopintrin.h, fma4intrin.h
#else
#include <immintrin.h>         // MS version of immintrin.h covers AVX, AVX2 and FMA3
#endif // __GNUC__
#elif SSE_INSTR_SET == 7
#include <immintrin.h>             // AVX
#elif SSE_INSTR_SET == 6
#include <nmmintrin.h>             // SSE4.2
#elif SSE_INSTR_SET == 5
#include <smmintrin.h>             // SSE4.1
#elif SSE_INSTR_SET == 4
#include <tmmintrin.h>             // SSSE3
#elif SSE_INSTR_SET == 3
#include <pmmintrin.h>             // SSE3
#elif SSE_INSTR_SET == 2
#define USE_SSE2
#include <emmintrin.h>             // SSE2
#elif SSE_INSTR_SET == 1
#include <xmmintrin.h>             // SSE

#endif // SIMD_CONFIG_H

union E
{
	__m128 e;
	float ef[3];
} ;


class  Vector3
{
private:
	E  vec3;

public:
	//float e[3];

	Vector3();
	Vector3(float e0, float e1, float e2);

	friend std::ostream& operator<<(std::ostream &os, const Vector3 &t);
	friend std::istream& operator >> (std::istream &is, Vector3 &t);

	// access operations
	inline float x() const { return vec3.ef[0]; }
	inline float y() const { return vec3.ef[1]; }
	inline float z() const { return vec3.ef[2]; }
	inline float r() const { return vec3.ef[0]; }
	inline float g() const { return vec3.ef[1]; }
	inline float b() const { return vec3.ef[2]; }

	// special operations
	Vector3 operator-() const { return Vector3(-vec3.e.m128_f32[0], -vec3.e.m128_f32[1], -vec3.e.m128_f32[2]); }
	Vector3 operator+() const { return *this; }
	float operator[](int i) const { return vec3.ef[i]; }
	float& operator[](int i) { return vec3.ef[i]; }

	// standard operations (+-/*)
	friend Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
	friend Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
	friend Vector3 operator/(const Vector3 &v1, const Vector3 &v2);
	friend Vector3 operator*(const Vector3 &v1, const Vector3 &v2);
	friend Vector3 operator*(const float &f, const Vector3 &v);
	friend Vector3 operator*(const Vector3 &v, const float &f);
	friend Vector3 operator/(const Vector3 &v, const float &f);

	// =(+-/*) operators
	Vector3& operator+=(const Vector3 &v2);
	Vector3& operator-=(const Vector3 &v2);
	Vector3& operator*=(const Vector3 &v2);
	Vector3& operator/=(const Vector3 &v2);
	Vector3& operator*=(float t);
	Vector3& operator/=(float t);

	// Vector Operations
	float length() const
	{
		return sqrt(vec3.e.m128_f32[0] * vec3.e.m128_f32[0] + vec3.e.m128_f32[1] * vec3.e.m128_f32[1] + vec3.e.m128_f32[2] * vec3.e.m128_f32[2]);
	}

	float squared_length() const
	{
		return vec3.e.m128_f32[0] * vec3.e.m128_f32[0] + vec3.e.m128_f32[1] * vec3.e.m128_f32[1] + vec3.e.m128_f32[2] * vec3.e.m128_f32[2];
	}

	void make_unit_vector();

	friend float dot(const Vector3 &v1, const Vector3 &v2);

	friend Vector3 cross(const Vector3 &v1, const Vector3 &v2);

	friend Vector3 unit_vector(Vector3 &v);

};
#endif // VECTOR3_H

