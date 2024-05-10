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