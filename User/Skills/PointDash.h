#pragma once
/**
 * @file PointDash.h
 * @brief
 */
#include <vector>

#include "DirectXCommon.h"
#include "Affin.h"
#include "Input.h"
#include "Easing.h"
#include "RayCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "ParticleManager.h"

// ポイントダッシュスキル
class PointDash
{
public:
	// 配列用
	enum POINTS {
		POINT_1 = 0,
		POINT_2 = 1,
		POINT_3 = 2,
		POINT_4 = 3,
		POINT_5 = 4,
		POINT_MAX = 5
	};

public:
	const uint32_t MAX_POINTNUM = POINT_MAX;
	std::vector<Vector3> points;
	Vector3 resultVec;
	float easeSpeed;
	float F_lengs;
	bool isActive;
	bool pointsMax;
private:
	Object3d* circleOBJ_[POINT_MAX];
	bool pointActive_[POINT_MAX];
	Model* model_;

	Vector3 startPos;
	Vector3 moveVec[5];
	float dashSpeed;
	uint32_t nowPointNum;
	uint32_t registNum;
	bool isReset;
	bool moveEnd;

	uint32_t time;
	uint32_t easeMaxTime = 40;
	float easetime;
	bool timeEnd = false;

	// パーティクル
	bool onPat_;
	std::unique_ptr <ParticleManager>  particle_;
	uint32_t onPatTime_;



	float debuglengs[POINT_MAX];
	float Padding__;
	std::unique_ptr<Object3d> lineOBJ_[POINT_MAX];
	Model* lineModel_;
	bool isLineActive_[POINT_MAX];
	bool PADIING__;

public:

	~PointDash();
	void Initialize();
	void Update(Vector3 pos, Vector3 ret);
	void Draw(DirectXCommon* dxCommon);
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

	void DebugImGui();

	uint32_t GetRegistNum() { return registNum; };
	bool GetLineActive(uint32_t num) { return isLineActive_[num]; };

	//コライダー
private:
	RayCollider* ray;
	RaycastHit* rayHit;
	Vector3 rayvec;
};

