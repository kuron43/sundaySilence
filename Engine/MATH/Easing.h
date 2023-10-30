#pragma once
#include <math.h>

#include "Vector2.h"
#include "Vector3.h"

namespace Easing
{
	// 線形補間
	float lerpFloat(const float start, const float end, const float time);
	// 二乗
	float InQuadFloat(const float start, const float end, const float time);
	float OutQuadFloat(const float start, const float end, const float time);
	float InOutQuadFloat(const float start, const float end, const float time);

	Vector2 InQuadVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 OutQuadVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 InOutQuadVec2(const Vector2& start, const Vector2& end, const float time);

	Vector3 InQuadVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 OutQuadVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 InOutQuadVec3(const Vector3& start, const Vector3& end, const float time);

	// 三乗
	float InCubicFloat(const float start, const float end, const float time);
	float OutCubicFloat(const float start, const float end, const float time);
	float InOutCubicFloat(const float start, const float end, const float time);

	Vector2 InCubicVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 OutCubicVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 InOutCubicVec2(const Vector2& start, const Vector2& end, const float time);

	Vector3 InCubicVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 OutCubicVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 InOutCubicVec3(const Vector3& start, const Vector3& end, const float time);

	// 四乗
	float InQuartFloat(const float start, const float end, const float time);
	float OutQuartFloat(const float start, const float end, const float time);
	float InOutQuartFloat(const float start, const float end, const float time);

	Vector2 InQuartVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 OutQuartVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 InOutQuartVec2(const Vector2& start, const Vector2& end, const float time);

	Vector3 InQuartVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 OutQuartVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 InOutQuartVec3(const Vector3& start, const Vector3& end, const float time);

	// 五乗
	float InQuintFloat(const float start, const float end, const float time);
	float OutQuintFloat(const float start, const float end, const float time);
	float InOutQuintFloat(const float start, const float end, const float time);

	Vector2 InQuintVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 OutQuintVec2(const Vector2& start, const Vector2& end, const float time);
	Vector2 InOutQuintVec2(const Vector2& start, const Vector2& end, const float time);

	Vector3 InQuintVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 OutQuintVec3(const Vector3& start, const Vector3& end, const float time);
	Vector3 InOutQuintVec3(const Vector3& start, const Vector3& end, const float time);
};

