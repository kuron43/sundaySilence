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
	Vector3 resultVec;
	float easeSpeed;
	bool isActive;
private:
	Object3d* object_[5];
	bool pointActive_[5];
	Model* model_;

	Vector3 startPos;
	Vector3 moveVec[5];
	float dashSpeed;
	uint32_t nowPointNum;
	uint32_t registNum;
	bool isReset;
	bool pointsMax;
	bool moveEnd;

	uint32_t time;
	uint32_t easeMaxTime = 30;
	float easetime;
	bool timeEnd = false;

public:

	~PointDash();
	void Initialize();
	void Draw();
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

