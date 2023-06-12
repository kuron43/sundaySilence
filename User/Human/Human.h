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
	Input* input;

	bool Slow = false;
public:

	Human();
	virtual ~Human();

	/// シーンの更新を行う
	virtual void Initialize() = 0;

	/// シーンの更新を行う
	virtual void Update(Input* input) = 0;

	/// シーンの描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

