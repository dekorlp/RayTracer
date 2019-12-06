#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

	class Vector3
	{
	public:
		float e[3];

		Vector3() {};
		Vector3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
		inline float x() const { return e[0]; }
		inline float y() const { return e[1]; }
		inline float z() const { return e[2]; }
		inline float r() const { return e[0]; }
		inline float g() const { return e[1]; }
		inline float b() const { return e[2]; }

		inline const Vector3& operator+() const { return *this; };
		inline Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
		inline float operator[](int i) const { return e[i]; }
		inline float& operator[](int i) { return e[i]; }

		inline Vector3& operator+=(const Vector3 &v2);
		inline Vector3& operator-=(const Vector3 &v2);
		inline Vector3& operator*=(const Vector3 &v2);
		inline Vector3& operator/=(const Vector3 &v2);
		inline Vector3& operator*=(float t);
		inline Vector3& operator/=(float t);

		inline float length() const 
		{
			return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		}

		inline float squared_length() const 
		{
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		inline void make_unit_vector();
	};
#endif // VECTOR3_H

	inline std::istream& operator >> (std::istream &is, Vector3 &t);

	inline std::ostream& operator<<(std::ostream &os, const Vector3 &t);


	inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2);

	inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2);

	inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2);

	inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2);

	inline Vector3 operator*(float t, const Vector3 &v);

	inline Vector3 operator/(const Vector3 &v, float t);

	inline Vector3 operator*(const Vector3 &v, float t);

	inline float dot(const Vector3 &v1, const Vector3 &v2);

	inline Vector3 cross(const Vector3 &v1, const Vector3 &v2);


	inline Vector3 unit_vector(Vector3 v);