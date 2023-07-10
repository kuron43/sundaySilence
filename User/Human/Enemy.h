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

	//
	void SetPos(Vector3 pos) { object_->wtf.position = pos; }
	void SetReticle(Vector3 ret) { reticle->wtf.position = ret; }

	// 種族番号取得
	int HowTribe() { return Tribe_; }

	Transform GetTransform() { return object_->wtf; }
	
public:
	Object3d* object_;
private:
	const int Tribe_ = 1;
	Model* model_;
	Vector3 faceAngle_;
	bool isDead = false;

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

