#pragma once
/**
 * @file PointDash.h
 * @brief
 */
#include <vector>

#include "Affin.h"
#include "Input.h"
#include "Easing.h"
#include"RayCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

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
	uint32_t easeMaxTime = 30;
	float easetime;
	Vector3 resultVec;
	bool timeEnd = false;

public:
	void Initialize();
	// 更新
	bool PointRayUpdate(Vector3 pos,Vector3 ret);
	// 地点登録
	void SetPoint(Vector3& point, Input* input);
	// 向かう方向のベクトル作成
	void MakeMoveVec(Vector3 pos);
	// 移動
	void GoToPoint();
	// リセット
	void Reset();

	//コライダー
private:
	RayCollider* ray;
	RaycastHit* rayHit;
	Vector3 rayvec;
};

