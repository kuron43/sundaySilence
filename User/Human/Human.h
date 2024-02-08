#pragma once
/**
 * @file Human.h
 * @brief ヒトガタ基底クラス
 */
#pragma warning(push)
#pragma warning(disable: 4514)
#include <imgui.h>
#pragma warning(pop)

#include "HumanList.h"

#include "FBXObject3d.h"
#include "Object3d.h"
#include "Transform.h"
#include "Affin.h"
#include "Input.h"

#include "DirectXCommon.h"

#include "Weaponlist.h"
#include "ParticleManager.h"

#include"SphereCollider.h"
#include"RayCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

 // ヒトガタ基底クラス
class Human
{

protected:
	float _SlowSpeed = 0.25f;
	bool _isSlow = false;
	bool _isTitle;
public:

	Human();
	virtual ~Human();

	/// 更新を行う
	virtual void Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input = nullptr, bool isTitle = false) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

	/// 武器の番号セット
	virtual void SetWeaponNum(uint32_t WeaponNum) = 0;
};

enum NUMBER {
	NUM_ZERO = 0,
	NUM_ONE = 1,
	NUM_TWO = 2,
	NUM_THREE,
	NUM_FOUR,
	NUM_FIVE,
	NUM_SIX,
	NUM_SEVEN,
	NUM_EIGHT,
	NUM_NINE,

	NUM_TEN = 10,

	NUM_TWENTY  = 20,
	NUM_TWENTYONE,
	NUM_TWENTYTWO,
	NUM_TWENTYTHREE,
	NUM_TWENTYFOUR,
	NUM_TWENTYFIVE,
	NUM_TWENTYSIX,
	NUM_TWENTYSEVEN,
	NUM_TWENTYEIGHT,
	NUM_TWENTYNINE,

	NUM_THIRTY = 30,
	NUM_THIRTYONE,
	NUM_THIRTYTWO,
	NUM_THIRTYTHREE,
	NUM_THIRTYFOUR,
	NUM_THIRTYFIVE,
	NUM_THIRTYSIX,
	NUM_THIRTYSEVEN,
	NUM_THIRTYEIGHT,
	NUM_THIRTYNINE,
};