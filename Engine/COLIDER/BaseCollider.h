#pragma once
#include "CollisionTypes.h"
#include "Object3d.h"
#include "CollisionInfo.h"
#include "RaycastHit.h"


//コライダー基底クラス
class BaseCollider
{
public:
	friend class CollisionManager;

public:
	BaseCollider() = default;
	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	inline void SetObject3d(Object3d* object)
	{
		object3d_ = object;
	}
	inline void RemoveObject3d()
	{
		object3d_ = nullptr;
	}

	inline Object3d* GetObject3d()
	{
		return object3d_;
	}

	//更新
	virtual void Update() = 0;
	//形状タイプ取得
	inline CollisionShapeType GetShapeType()
	{
		return shapeType;
	}

	inline void OnCllision(const CollisionInfo& info)
	{
		isHit = true;
		colInfo_ = info;
	}

	inline void SetAttribute(unsigned short attribute)
	{
		attribute_ = attribute;
	}

	unsigned short GetAttribute() {
		return attribute_;
	}

	inline void AddAttribute(unsigned short attribute)
	{
		attribute_ |= attribute;
	}

	inline void RemoveAttribute(unsigned short attribute)
	{
		attribute_ &= !attribute;
	}

	inline bool GetIsHit()
	{
		return isHit;
	}

	inline CollisionInfo GetCollisionInfo()
	{
		return colInfo_;
	}

protected:
	Object3d* object3d_ = nullptr;

	bool isHit = false;

	CollisionInfo colInfo_ = {
		nullptr ,
		nullptr ,
		{0 , 0 , 0},
		0.0f
	};

	//形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	//当たり判定属性
	unsigned short attribute_ = 0b1111111111111111;
};