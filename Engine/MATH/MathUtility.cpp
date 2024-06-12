#include "MathUtility.h"


//乱数生成装置(メルセンヌ・ツイスタ)
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());

float MathUtility::Randoms::GetRandFloat(const float min, const float max) {

	//乱数
	std::uniform_real_distribution<float>dist(min, max);
	float result;
	result = dist(engine) ;

	return result;
}

 /// <summary>
/// 度数法 -> ラジアン
/// </summary>
 float MathUtility::radConvert(float value) {
	 float radValue;

	 radValue = value * (PI / 180);

	 return radValue;
 }

 /// <summary>
 /// ラジアン -> 度数法
 /// </summary>
 float MathUtility::degConvert(float value) {
	 float degValue;

	 degValue = value * (180 / PI);

	 return degValue;
 }


 //sin、cosを両方出す
 void MathUtility::SinCos(float& sin_, float& cos_, float angle)
 {
	 sin_ = sin(angle);
	 cos_ = cos(angle);
 }

 Vector2 MathUtility::SinCosToVec2(const float angle)
 {
	 Vector2 result;
	 result.x = sin(angle);
	 result.y = cos(angle);
	 return result;
 }
