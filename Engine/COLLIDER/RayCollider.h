#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

class RayCollider : public BaseCollider, public Ray
{
public:
	RayCollider(Vector3 start = { 0.0f , 0.0f , 0.0f }, Vector3 dir = { 0.0f,0.0f,0.0f });

	//更新
	void Update() override;

	void SetStart(Vector3 start);

	Vector3 GetStart();

	void SetDir(Vector3 dir);

	Vector3 GetDir();

private:
	//オブジェクト中心からのオフセット
	Vector3 start_;
	//方向ベクトル
	Vector3 dir_;

};

