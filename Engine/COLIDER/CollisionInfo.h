#pragma once
//#include "MathFunc.h"

class Object3d;
class BaseCollider;

//衝突情報
struct CollisionInfo
{
public:
	CollisionInfo(Object3d* object , BaseCollider* collider , const Vector3 inter)
	{
		object_ = object;
		collider_ = collider;
		inter_ = inter;
	}

	//衝突相手のオブジェクト
	Object3d* object_ = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider_ = nullptr;
	//衝突ten
	Vector3 inter_;

};