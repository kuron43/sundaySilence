#pragma once
#include "Human.h"


class Player :
	public Human
{
public:
	Player();
	~Player()override;


	/// シーンの更新を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input,bool isTitle = false)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

	void Move(Input* input);

	// 種族番号取得
	int HowTribe() { return Tribe_; }

private:
	const int Tribe_ = 0;
	bool nowTitle = false;

	Model* model_;
	Object3d* object_;
	Object3d* reticle;
	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
	//移動速度
	const float kMoveSpeed_ = 0.5f;
	//旋回速度
	const float kTurnSpeed_ = Affin::radConvert(10);
	bool isRun_ = false;
	//移動ベクトル
	Vector3 velocity_;
	Vector3 faceAngle_;


	Weapon* weapon_[2];
	bool isWeaponOn = true;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	int SPHERE_COLISSION_NUM;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	Ray* ray;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;

};

