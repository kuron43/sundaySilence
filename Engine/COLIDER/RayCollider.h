#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

class RayCollider : public BaseCollider, public Ray
{
public:
	RayCollider(Vector3 start = { 0.0f , 0.0f , 0.0f }, Vector3 dir = { 0.0f,0.0f,0.0f }) :
		start_(start),
		dir_(dir)
	{
		//球形状をセット
		shapeType = COLLISIONSHAPE_RAY;
	}

	//更新
	void Update() override;

	inline void SetStart(Vector3 start)
	{
		start_ = start;
	}

	Vector3 GetStart()
	{
		return start_;
	}

	inline void SetDir(Vector3 dir)
	{
		dir_ = dir;
	}

	Vector3 GetDir()
	{
		return dir_;
	}

private:
	//オブジェクト中心からのオフセット
	Vector3 start_;
	//方向ベクトル
	Vector3 dir_;

};

