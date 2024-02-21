#pragma once
/**
 * @file Player.h
 * @brief
 */
#include "Human.h"

#include "SkillIntegrate.h"
#include "Sprite.h"


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
	/// 武器の番号セット
	void SetWeaponNum(uint32_t WeaponNum) override;

	void SetPos(Vector3 pos) { object_->wtf.position = pos; };
	void MatUpdate() { object_->UpdateMatrix(); };
	Transform GetTransform() { return object_->wtf; };
	Transform GetReticleTransform() { return reticle->wtf; };
	bool GetIsDeath() { return isDeath_; };
	bool GetIsSlow() { return _isSlow; }
	bool GetOnFire() { return isOnFire; }
	bool GetPointMAX() { return pointDash_->pointsMax; }
	uint32_t GetHP() { return hp_; };
	uint32_t GetHIT() { return hit_; };
	const uint32_t GetMAXHP() { return MAX_HP; };

	// 種族番号取得
	uint32_t HowTribe() { return Tribe_; };
private:
	void Move(Input* input);
	void FaceAngleUpdate();
	void HitMyColor();
	void ColisionUpdate();
	void OnColision(bool bullet);
	void PhantomUpdate();
private:
	const uint32_t Tribe_ = HU_PLAYER;
	uint32_t useWeapon_ = WP_ASSAULT;
	bool nowTitle = false;


	Model* model_;
	Model* reticleMD_;
	Model* reticleXMD_;
	Object3d* object_;
	Object3d* reticle;
	Transform shotPos;
	float mouseSensitivity_ = 0.15f;	//マウス感度 元0.99
	//移動速度
	const float kMoveSpeed_ = 0.0f;
	//旋回速度
	const float kTurnSpeed_ = Affin::radConvert(10);
	bool isRun_ = false;
	//移動ベクトル
	//float slowPalams = 0.25f;
	Vector3 velocity_;
	Vector3 faceAngle_;


	Weapon* weapon_[2];
	bool isOnFire = true;

	uint32_t coolTimeFB_;
	bool onFireBottle = false;

	// 残像用
	Object3d* phantom_[4];
	float phantomAlpha_[4];
	bool isPhantom_;
	bool pad[3];
	uint32_t countPH_;
	// スキル用
private:
	PointDash* pointDash_;
	bool nowSetPoint;
	bool wallHit;
	// 前フレーム移動ベクトル
	Vector3 oldVelocity_;

private:
	const uint32_t MAX_HP = 30;
	uint32_t hp_ = MAX_HP;
	uint32_t hit_;
	bool isDeath_;
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
	Ray* ray;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;
	Model* colPosTesM_;

};

