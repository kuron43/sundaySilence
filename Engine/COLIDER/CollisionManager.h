#pragma once
#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include <forward_list>
#include <d3d12.h>

class BaseCollider;

class CollisionManager
{
public:
	static CollisionManager* GetInstance();

	//メンバ関数
public:
	//コライダーの追加
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.push_front(collider);
	}

	//コライダーの削除
	inline void RemoveCollider(BaseCollider* collider)
	{
		colliders.remove(collider);
	}

	void CheckAllCollisions();
	bool Raycast(const Ray& ray , unsigned short attribute, RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray , RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator= (const CollisionManager&) = delete;

	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;

};