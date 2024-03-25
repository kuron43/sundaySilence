/**
 * @file Weapon.h
 * @brief
 */
#pragma once
#include "Model.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "ImGui.h"
#include "Transform.h"
#include "Bullet.h"
#include "BulletManager.h"

// 武器基底クラス
class Weapon
{
protected:
	float _slowSpeed = 0.25f;
	static bool _isSlow;
public:
	static void SetIsSlow(bool isSlow) { _isSlow = isSlow; };
	Weapon();
	virtual ~Weapon();

	virtual Weapon* Create();
	/// 更新を行う
	virtual bool Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input/*,bool isSlow*/) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

	// 発射を行う
	virtual void Shot(Transform& player, Transform& reticle, uint32_t team) = 0;

	
};

