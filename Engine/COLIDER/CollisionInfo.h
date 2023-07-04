#pragma once
#include "MathFunc.h"

class Object3d;
class BaseCollider;

//衝突情報
struct CollisionInfo
{
public:
	CollisionInfo(Object3d* object , BaseCollider* collider , const Vector3 inter)
	{
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//衝突相手のオブジェクト
	Object3d* object = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突店
	Vector3 inter;

};