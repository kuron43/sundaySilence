#pragma once
/**
 * @file Enemy.h
 * @brief
 */
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
	void Update(Input* input = nullptr, bool isTitle = false)override;

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon)override;

	/// リセットを行う
	void Reset() override;

	/// 武器の番号セット
	void SetWeaponNum(uint32_t WeaponNum) override;

	// セッター
	void SetPos(Vector3 pos) { object_->transForm.position = pos; }
	void SetReticle(Vector3 ret) { reticle.position = ret; }
	void SetRestRotate(Vector3 rot) { restRotate_ = rot; }
	void SetModel(Model* md) { model_ = md; }

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
	std::unique_ptr<Object3d> object_;
private:
	const uint32_t Tribe_ = HU_ENEMY;
	uint32_t useWeapon_ = WP_ASSAULT;
	bool StartFrontRot = false;
	bool isFound = false;
	bool oldFound = false;
	bool isFire = false;
	bool isBlocked = false;
	bool isDead = false;
	bool onPat_;
	bool isHitEffect;


	Model* model_;
	std::unique_ptr<Model> colliderPosTest_MD;
	Transform reticle;

	Vector3 frontVec_;
	int32_t hp = 3;


	
	//移動速度
	const float kMoveSpeed_ = 0.5f;
	//移動ベクトル
	Vector3 velocity_;
	// 回転向き保存
	Vector3 restRotate_;
	Vector3 stateRotate_;
	// イージング用
	uint32_t easeTimer;
	uint32_t easeMaxTime = 50;
	float easetime;
	bool isEaseEnd = false;
	bool isLost = false;


	bool isWeaponOn = true;
	bool nowTitle = false;
	std::unique_ptr<Weapon> weapon_;

	// パーティクル
	std::unique_ptr <ParticleManager>  particle_;
	uint32_t onPatTime_;

	// 体の色変化
	const uint32_t MAX_HITTIME = 5;
	uint32_t hitTime_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	uint32_t SPHERE_COLLISION_NUM = 1;	//コライダー（スフィア）の数
	//std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<std::unique_ptr<Object3d>> colliderPosTest_;
	RayCollider* ray;
	RaycastHit* rayHit;
	Vector3 rayvec;
	uint32_t PADDING;

private:
	//代入演算子削除
	Enemy& operator=(const Enemy&) = delete;
	//コピーコンストラクタ削除
	Enemy(const Enemy&) = delete;
};

