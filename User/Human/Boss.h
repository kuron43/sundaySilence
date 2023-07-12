#pragma once
#include "Human.h"

class Boss :
    public Human
{
public:
	Boss();
	~Boss()override;


	/// シーンの更新を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input, bool isTitle = false)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

	// 種族番号取得
	int HowTribe() { return Tribe_; }


private:
	const int Tribe_ = 2;

	Model* model_;
	Object3d* object_;
	Vector3 frontVec_;

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

