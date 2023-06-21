#pragma once
#include "Object3d.h"
#include "Transform.h"
#include "Affin.h"
#include "Input.h"

#include "DirectXCommon.h"

// 基底クラス
class Human
{

protected:

	bool isSlow = false;
	float slowSpeed = 0.25f;
public:

	Human();
	virtual ~Human();

	/// 更新を行う
	virtual void Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

};

