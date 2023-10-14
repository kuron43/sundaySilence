#pragma once
#include "Affin.h"
#include "Input.h"
#include <vector>
#include "Easing.h"

// ポイントダッシュスキル
class PointDash
{
public:
	const uint32_t MAX_POINTNUM = 5;
	std::vector<Vector3> points;
	Vector3 startPos;
	Vector3 moveVec[5];
	float dashSpeed;
	float easeSpeed;
	uint32_t nowPointNum;
	uint32_t registNum;
	bool isReset;
	bool pointsMax;
	bool moveEnd;
	bool isActive;

	uint32_t time;
	float easetime;
	uint32_t easeMaxTime = 30;
	bool timeEnd = false;
	Vector3 resultVec;

public:
	// 更新
	void Update(Vector3 pos);
	// 地点登録
	void SetPoint(Vector3& point, Input* input);
	// 向かう方向のベクトル作成
	void MakeMoveVec(Vector3 pos);
	// 移動
	void GoToPoint();
	// リセット
	void Reset();


};

