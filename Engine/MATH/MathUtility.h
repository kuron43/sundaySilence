#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "ConvertXM.h"
#include "Easing.h"
#include "Affin.h"

#include <random>

namespace MathUtility
{
	namespace Randoms {
		float GetRandFloat(const float min, const float max);
	};

	//円周率
	const float PI = 3.141592654f;
	// 度数法 -> ラジアン変換
	float radConvert(float value);
	// ラジアン -> 度数法変換
	float degConvert(float value);

	//sin、cosを両方出す
	void SinCos(float& sin_, float& cos_, float angle);
	//sin、cosを両方Vector2にまとめて出す |x=>sin|y=>cos|
	Vector2 SinCosToVec2(const float angle);

};

