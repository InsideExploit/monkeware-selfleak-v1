#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define M_PI 3.14159265358979323846264338327950288419716939937510

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	float x;
	float y;


	bool equals(Vector2 other) {
		return (x == other.x && y == other.y);
	}

};

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& vector) const;
	Vector3 operator-(const Vector3& vector) const;
	Vector3 operator-() const;
	Vector3 operator*(float number) const;
	Vector3 operator/(float number) const;

	Vector3& operator+=(const Vector3& vector);
	Vector3& operator-=(const Vector3& vector);
	Vector3& operator*=(float number);
	Vector3& operator/=(float number);

	bool operator==(const Vector3& vector) const;
	bool operator!=(const Vector3& vector) const;

	inline float Dot(const Vector3& vector)
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	inline float Distance(const Vector3& vector)
	{
		float xCoord = vector.x - x;
		float yCoord = vector.y - y;
		float zCoord = vector.z - z;
		return sqrtf((xCoord * xCoord) + (yCoord * yCoord) + (zCoord * zCoord));
	}

	inline float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	inline void Rotate2D(float angle)
	{
		// use local variables to find transformed components
		float Vx1 = cosf(angle) * x - sinf(angle) * y;
		float Vy1 = sinf(angle) * x + cosf(angle) * y;
		// store results thru the pointer
		x = Vx1;
		y = Vy1;

		return;
	}

	inline void Clamp()
	{
		if (x > 75.f) x = 75.f;
		else if (x < -75.f) x = -75.f;
		if (z < -180) z += 360.0f;
		else if (z > 180) z -= 360.0f;

		y = 0.f;
	}
};

inline bool Vector3::operator==(const Vector3& vector) const
{
	return x == vector.x && y == vector.y && z == vector.z;
}

inline bool Vector3::operator!=(const Vector3& vector) const
{
	return x != vector.x || y != vector.y || z != vector.z;
}

inline Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

inline Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

inline Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator*(float number) const
{
	return Vector3(x * number, y * number, z * number);
}

inline Vector3 Vector3::operator/(float number) const
{
	return Vector3(x / number, y / number, z / number);
}

inline Vector3::Vector3()
{
}

inline Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

inline Vector3& Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

inline Vector3& Vector3::operator*=(float number)
{
	x *= number;
	y *= number;
	z *= number;

	return *this;
}

inline Vector3& Vector3::operator/=(float number)
{
	x /= number;
	y /= number;
	z /= number;

	return *this;
}

//Quickly needed for distance calculations
float DistanceVec2(Vector2 src, Vector2 dst)
{
	float distance;
	distance = sqrtf(powf(src.x - dst.x, 2) + powf(src.y - dst.y, 2));
	return distance;
}

float DistanceVec3(Vector3 src, Vector3 dst)
{
	float distance;
	distance = sqrtf(powf(src.x - dst.x, 2) + powf(src.y - dst.y, 2) + powf(src.z - dst.z, 2));
	return distance;
}

class Vector4
{
public:
	Vector4() : x(0.f), y(0.f), z(0.f), w(0.f)
	{

	}

	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{

	}
	~Vector4()
	{

	}

	float x;
	float y;
	float z;
	float w;
};

#endif