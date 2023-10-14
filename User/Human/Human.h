#pragma once
#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)

#include "Object3d.h"
#include "Transform.h"
#include "Affin.h"
#include "Input.h"

#include "DirectXCommon.h"

#include "Weapon.h"
#include "ParticleManager.h"

#include"SphereCollider.h"
#include"RayCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

// ヒトガタ基底クラス
class Human
{

protected:

	bool isSlow = false;
	float slowSpeed = 0.25f;
	bool _isTitle;
public:

	Human();
	virtual ~Human();

	/// 更新を行う
	virtual void Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input = nullptr,bool isTitle = false) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

};

