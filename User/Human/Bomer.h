#pragma once
/**
 * @file Bomer.h
 * @brief
 */
#include "Human.h"
#include "Weaponlist.h"

class Bomer :
	public Human
{
public:
	Bomer();
	~Bomer()override;


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
	void SetPos(Vector3 pos) { object_->wtf.position = pos; }
	void SetReticle(Vector3 ret) { reticle->wtf.position = ret; }
	void SetRestRotate(Vector3 rot) { restRotate_ = rot; }

	// 種族番号取得
	uint32_t HowTribe() { return Tribe_; }
	bool HowDead() { return isDead; }

	Transform GetTransform() { return object_->wtf; }

private:
	//正面をレティクル方向に向かせる
	void FrontFace();
	// 当たり判定用のアップデート
	void ColiderUpdate();
	void OnColision();

	void HitMyColor();
public:
	Object3d* object_;
private:
	const uint32_t Tribe_ = HU_BOMER;
	uint32_t useWeapon_ = WP_ASSAULT;
	bool StartFrontRot = false;
	bool isFound = false;
	bool oldFound = false;
	bool isFire = false;
	bool isBlocked = false;


	Model* model_;
	Object3d* reticle;

	Vector3 frontVec_;
	bool isDead = false;
	uint32_t hp = 2;


	//移動速度
	const float kMoveSpeed_ = 0.5f;
	bool isRun_ = false;
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


	Weapon* weapon_;
	bool isWeaponOn = true;

	// タイトル用の処理と切り分けるためのやつ
	bool nowTitle = false;

	// パーティクル
	std::unique_ptr <ParticleManager>  particle_;
	uint32_t onPatTime_;
	bool onPat_;

	// 体の色変化
	bool isHitEffect;
	const uint32_t MAX_HITTIME = 5;
	uint32_t hitTime_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	uint32_t SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;
	RayCollider* ray;
	RaycastHit* rayHit;
	Vector3 rayvec;

private:
	//代入演算子削除
	Bomer& operator=(const Bomer&) = delete;
	//コピーコンストラクタ削除
	Bomer(const Bomer&) = delete;
};


