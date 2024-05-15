#pragma once
/**
 * @file Boss.h
 * @brief
 */
#include "Human.h"
#include "Weaponlist.h"
#include "BossManager.h"

class Boss :
	public Human
{
public:
	Boss();
	~Boss()override;

	/// シーンの初期化を行う
	void Initialize()override;

	/// シーンの更新を行う
	void Update(Input* input = nullptr, bool isTitle = false)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

	/// 武器の番号セット
	void SetWeaponNum(uint32_t WeaponNum) override;

	// セッター
	void SetPos(Vector3 pos) { object_->transForm.position = pos; }
	void SetReticle(Vector3 ret) { reticle->transForm.position = ret; }
	void SetRestRotate(Vector3 rot) { restRotate_ = rot; }

	void SetFBXModel(FBXModel* model) { bossFbxM_ = model; }

	// 種族番号取得
	uint32_t HowTribe() { return Tribe_; }
	bool HowDead() { return isDead; }

	Transform GetTransform() { return object_->transForm; }

private:
	//正面をレティクル方向に向かせる
	void FrontFace();
	// 当たり判定用のアップデート
	void ColliderUpdate();
	void OnCollision();

	void HitMyColor();
public:
	Object3d* object_;
	FBXModel* bossFbxM_;
	std::unique_ptr<FBXObject3d> bossFbxO_;
	Weapon* weapon_;

//private:
	uint32_t stateNum_ = 0;
	const uint32_t Tribe_ = HU_BOSS;
	uint32_t useWeapon_ = WP_ASSAULT;
	bool isWeaponOn = true;
	bool isFound = false;
	bool isFire = false;
	bool isFireOld = false;
	bool isBlocked = false;
	bool isDead = false;
	bool nowTitle = false;
	bool onPat_;
	bool isHitEffect;
	bool PADDING[3];

	Model* model_;
	Model* modelCol_;
	Object3d* reticle;

	Vector3 frontVec_;
	uint32_t hp = 10;

	std::unique_ptr<BossManager> manager_;

	//移動速度
	const float kMoveSpeed_ = 0.5f;
	//移動ベクトル
	Vector3 velocity_;
	// 初期回転向き保存
	Vector3 restRotate_;

	// パーティクル関係
	uint32_t onPatTime_;
	ObjParticleManager::ParticlePreset patPreset_;

	// 体の色変化
	const uint32_t MAX_HITTIME = 5;
	uint32_t hitTime_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	Vector3 rayvec;
	uint32_t SPHERE_COLLISION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> colliderPosTest_;
	RayCollider* ray;
	RaycastHit* rayHit;
};

