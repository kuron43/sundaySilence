#pragma once

class Object3d;
class BaseCollider;

//衝突情報
struct CollisionInfo
{
public:
	CollisionInfo()
	{
		object_ = nullptr;
		collider_ = nullptr;
		inter_ = {0,0,0};
		distance_ = 0.0f;
	}
	CollisionInfo(Object3d* object , BaseCollider* collider , const Vector3 inter, float distance = 0.0f)
	{
		object_ = object;
		collider_ = collider;
		inter_ = inter;
		distance_ = distance;
	}

	//衝突相手のオブジェクト
	Object3d* object_ = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider_ = nullptr;
	//衝突ten
	Vector3 inter_;

	float distance_;

};