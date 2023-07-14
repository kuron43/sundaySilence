#pragma once
#include "Object3d.h"
#include "Transform.h"
#include "Affin.h"

#include"ObbCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

class DirectXCommon;

class Objects
{
public:
	Objects();
	virtual ~Objects();

	/// 更新を行う
	virtual void Initialize(Model* model) = 0;

	/// 更新を行う
	virtual void Update() = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

};

