#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2::length()const {

	return (sqrt(x) * sqrt(x)) + (sqrt(y) * sqrt(y));
}

Vector2& Vector2::nomalize() {
	float len = length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector2::dot(const Vector2& v) const {
	return (this->x * v.x) + (this->y * v.y);
}

float Vector2::cross(const Vector2& v)const {
	return (this->x * v.y) - (this->y * v.x);
}

Vector2 Vector2::operator+()const {
	return *this;
}

Vector2 Vector2::operator-()const {
	return Vector2(-(*this));         ////
}

Vector2& Vector2::operator+=(const Vector2& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s) {
	this->x *= s;
	this->y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s) {
	this->x /= s;
	this->y /= s;
	return *this;
}

//Vector2D　クラスに属さない関数群
//二項演算子
const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 temp(v1);
	return temp + v2;
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	Vector2 temp(v1);
	return temp - v2;
}

const Vector2 operator*(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp * s;
}

const Vector2 operator*(float s, const Vector2& v) {
	return s * v;
}

const Vector2 operator/(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp / s;
}