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

		float length() const 
		{
			return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		}

		float squared_length() const 
		{
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		void make_unit_vector();
	
		friend Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
		friend std::istream& operator >> (std::istream &is, Vector3 &t);

		friend std::ostream& operator<<(std::ostream &os, const Vector3 &t);




		friend Vector3 operator-(const Vector3 &v1, const Vector3 &v2);

		friend Vector3 operator*(const Vector3 &v1, const Vector3 &v2);

		friend Vector3 operator/(const Vector3 &v1, const Vector3 &v2);

		friend Vector3 operator*(float t, const Vector3 &v);

		friend Vector3 operator/(const Vector3 &v, float t);

		friend Vector3 operator*(const Vector3 &v, float t);

		friend float dot(const Vector3 &v1, const Vector3 &v2);

		friend Vector3 cross(const Vector3 &v1, const Vector3 &v2);


		friend Vector3 unit_vector(Vector3 v);
	
	};
#endif // VECTOR3_H

	