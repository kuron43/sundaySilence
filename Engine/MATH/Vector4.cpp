#include "Vector4.h"

#include<cmath>  //sprt

Vector4::Vector4() :x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::Length()const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalization() const
{
	Vector4 tmp(*this);

	float len = Length();
	if (len != 0)
	{
		return tmp /= len;

	}

	return tmp;
}

Vector4& Vector4::Normalize() {
	float len = Length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector4::Dot(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::Cross(const Vector4& v) const
{
	return Vector4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		v.w
	);
}

Vector4 Vector4::operator+() const
{
	return Vector4(x, y, z, w);
}

Vector4 Vector4::operator-() const
{
	return Vector4(x, y, z, w);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

Vector4& Vector4::operator*=(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}



const Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1);
	return temp + v2;
}

const Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1);
	return temp - v2;
}

const Vector4 operator*(const Vector4& v, float s)
{
	Vector4 temp(v);
	return temp * s;
}

const Vector4 operator*(float s, const Vector4& v)
{
	return v * s;
}

const Vector4 operator/(const Vector4& v, float s)
{
	Vector4 temp(v);
	return temp / s;
}