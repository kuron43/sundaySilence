#pragma once
#include "Human.h"
#include "Weapon.h"


class Player :
    public Human
{
public:
	Player();
	~Player()override;


	/// シーンの更新を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	 void Reset() override;

	void Move(Input* input);

private:
	Model* model_;
	Object3d* object_;
	//移動速度
	const float kMoveSpeed_ = 0.5;
	//移動ベクトル
	Vector3 velocity_;
	Vector3 faceAngle_;


};

