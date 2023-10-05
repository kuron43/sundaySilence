#pragma once
#include "Human.h"
#include "Weaponlist.h"

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

	//
	void SetPos(Vector3 pos) { object_->wtf.position = pos; }
	void SetReticle(Vector3 ret) { reticle->wtf.position = ret; }
	void SetRestRotate(Vector3 rot) { restRotate_ = rot; }

	// 種族番号取得
	uint32_t HowTribe() { return Tribe_; }
	bool HowDead() { return isDead; }

	Transform GetTransform() { return object_->wtf; }

private:
	void FrontFace();
	void ColiderUpdate();
	void OnColision();

public:
	Object3d* object_;
private:
	const uint32_t Tribe_ = 1;
	bool isFound = false;
	bool isFire = false;
	bool isBlocked = false;


	Model* model_;
	Object3d* reticle;

	Vector3 frontVec_;
	bool isDead = false;
	uint32_t hp = 10;


	//移動速度
	const float kMoveSpeed_ = 0.5f;
	bool isRun_ = false;
	//移動ベクトル
	Vector3 velocity_;
	// 初期回転向き保存
	Vector3 restRotate_;


	Weapon* weapon_;
	bool isWeaponOn = true;

	// タイトル用の処理と切り分けるためのやつ
	bool nowTitle = false;

	// パーティクル関係
	ParticleManager* particle_ = nullptr;
	uint32_t onPatTime_;
	bool onPat_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	uint32_t SPHERE_COLISSION_NUM;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;
	RayCollider* ray;
	RaycastHit* rayHit;
	Vector3 rayvec;
};

