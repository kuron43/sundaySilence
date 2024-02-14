#pragma once
#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include "QueryCallback.h"
#include "ObbCollider.h"

#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#pragma warning(disable: 4820)
#include <forward_list>
#include <d3d12.h>

#pragma warning(pop)

class BaseCollider;

class CollisionManager
{
public:
	static CollisionManager* GetInstance();

	//メンバ関数
public:
	inline void Finalize() {

		colliders.clear();
	}
	//コライダーの追加
	inline void AddCollider(BaseCollider* collider)
	{
		colliders.emplace_front(collider);
	}

	//コライダーの削除
	inline void RemoveCollider(BaseCollider* collider)
	{
		collider->RemoveObject3d();
		colliders.remove(collider);
	}

	void CheckAllCollisions();
	bool Raycast(const Ray& ray , unsigned short attribute, RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);
	bool Raycast(const Ray& ray , RaycastHit* hitInfo = nullptr , float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// 球による衝突全検索
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="callback">衝突時コールバック</param>
	/// <param name="attribute">対象の属性</param>
	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffff);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator= (const CollisionManager&) = delete;

	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;

public:
	static uint32_t OBBHitFace(OBB& obb, Sphere& sphere);
	static bool OBBToSphereCollision(OBB& obb, Sphere& sphere);
	static float LenOBBToPoint(OBB& obb,Vector3 & p);
	static bool PlaneToSphere(FinitePlane plane, Sphere& sphere);
	static float PlaneToPointLeng(FinitePlane plane, Vector3 pos, float radius, float& angle);
	static bool PlaneToPointInside(FinitePlane plane, Vector3 pos);
	static bool PolygonToPointInside(std::vector<Vector3> polygonPos, Vector3 pos);
	static float LineToPointLeng(Vector3 lineVertex1, Vector3 lineVertex2, Vector3 pointPos);
private:



};