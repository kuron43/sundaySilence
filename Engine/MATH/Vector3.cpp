#include "Vector3.h"

#include <cmath>

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::InIt()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;	
}

float Vector3::length()const {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3& Vector3::nomalize() {
	float len = length();
	if (len != 0) {
		return *this /= length();
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const {
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

Vector3 Vector3::cross(const Vector3& v) const {
	return Vector3((this->y * v.z) - (this->z * v.y), (this->z * v.x) - (this->x * v.z), (this->x * v.y) - (this->y * v.x));
}

const Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const float t) {
	/*float y = t;
	return start * (1.0f - y) + end * y;*/
	return start * (1.0f - t) + end * t;
}

Vector3 Vector3::operator+()const {
	return *this;
}

Vector3 Vector3::operator-()const {

	return Vector3(-x, -y, -z);         ////
}

Vector3& Vector3::operator+=(const Vector3& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float s) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s) {
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

//Vector2D　クラスに属さない関数群
//二項演算子
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	temp.x += v2.x;
	temp.y += v2.y;
	temp.z += v2.z;
	return temp;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	temp.x -= v2.x;
	temp.y -= v2.y;
	temp.z -= v2.z;
	return temp;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	temp.x *= s;
	temp.y *= s;
	temp.z *= s;
	return temp;
}

const Vector3 operator*(float s, const Vector3& v) {

	Vector3 result;
	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return result;
}

const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	temp.x /= s;
	temp.y /= s;
	temp.z /= s;
	return temp;
}