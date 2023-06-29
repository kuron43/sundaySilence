#pragma once
#include "Human.h"
#include "Weaponlist.h"

class Enemy :
    public Human
{
public:
	Enemy();
	~Enemy()override;


	/// シーンの更新を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input, bool isTitle = false)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

private:
	Model* model_;
	Object3d* object_;
	Vector3 faceAngle_;

	Object3d* reticle;
	
	//移動速度
	const float kMoveSpeed_ = 0.5f;
	bool isRun_ = false;
	//移動ベクトル
	Vector3 velocity_;


	Weapon* weapon_;
	bool isWeaponOn = true;

	// タイトル用の処理と切り分けるためのやつ
	bool nowTitle = false;
};

