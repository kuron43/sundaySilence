#pragma once
#include "Model.h"
#include "DirectXCommon.h"

class Input;
//class DirectXCommon;
class Transform;

class Weapon
{
protected:
	static Model* bullet_MD;

public:
	Weapon();
	virtual ~Weapon();

	virtual Weapon* Create();
	/// 更新を行う
	virtual bool Initialize() = 0;

	/// 更新を行う
	virtual void Update(Input* input,bool isSlow) = 0;

	/// 描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	/// リセットを行う
	virtual void Reset() = 0;

	// 発射を行う
	virtual void Shot(Transform& player, Transform& reticle) = 0;

	void SetBullModel(Model* model) { Weapon::bullet_MD = model; }
};

