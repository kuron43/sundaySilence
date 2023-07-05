#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"
//#include "MathFunc.h"

class SphereCollider : public BaseCollider , public Sphere
{
public:
	SphereCollider(Vector3 offset = {0 , 0 , 0} , float radius = 1.0f) :
		offset(offset) ,
		radius_(radius)
	{
		//球形状をセット
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	//更新
	void Update() override;

	inline void SetRadius(float radius)
	{
		radius_ = radius; 
	}
	
	float GetRadius()
	{
		return radius_; 
	}
	
	inline void SetBasisPos(Vector3* pos)
	{
		basisPos = pos;
	}

	Vector3 GetBasisPos()
	{
		return *basisPos;
	}

private:
	//オブジェクト中心からのオフセット
	Vector3 offset;

	//モデルがない場合の基準となるベクトル
	Vector3* basisPos = nullptr;

	//半径
	float radius_;

};

