#pragma once

#include <DirectXMath.h>

class Vector3
{
public:


	float x;
	float y;
	float z;

public:


	Vector3();
	Vector3(float x, float y, float z);


	float length() const;
	Vector3& nomalize();
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;
	static const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	static Vector3 Vector3Zero();
	static bool Vector3Equal(Vector3 v1,Vector3 v2);
	 bool Vector3IsInfinite();

	Vector3 operator+() const;
	Vector3 operator-() const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);

	//Vector3& operator=(const XMFLOAT3& v);
	//XMFLOAT3& operator=(const Vector3& v);
};

const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

