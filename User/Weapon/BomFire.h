#pragma once
/**
 * @file BomFire.h
 * @brief
 */
#include "Weapon.h"

 // 火炎瓶?
class BomFire :
	public Weapon
{
private:
	Model* model_;
	const uint32_t WeaponNum = 1;
	uint32_t team_;


private:
	const float nomalSpeed = 0.5f;
	float speed_ = nomalSpeed;
	uint32_t coolTime = 0;
	uint32_t mag = 0;
	uint32_t roadingTime = 0;

	bool active_ = false;
	bool goShot;
	uint16_t padding;

public:
	BomFire();
	~BomFire();

	/// 更新を行う
	bool Initialize() override;

	/// 更新を行う
	void Update(Input* input, bool isSlow) override;

	/// 描画を行う
	void Draw(DirectXCommon* dxCommon) override;

	/// リセットを行う
	void Reset() override;

	// 発射を行う
	void Shot(Transform& player, Transform& reticle, uint32_t team) override;

private:

	//代入演算子削除
	BomFire& operator=(const BomFire&) = delete;

	//コピーコンストラクタ削除
	BomFire(const BomFire&) = delete;
};

class FireBottle:public Bullet {
public:
	uint32_t team_;
	uint32_t weapon;
	bool isTeam;
	bool isDead;

	uint32_t DEATH_TIME_BOTTLE = 300;
	uint32_t deathCount;
	uint32_t timeCount;

	Object3d* bottleObj_;
	static Model* bulletModel_;

	Vector3 moveVec;
	float vecLength;

	const uint32_t MAX_HIGHT = 60;
	uint32_t bottle_Y_HIGHT = 0;
	
	const uint32_t MAX_FIRETIME = 60;
	uint32_t fireTime;
	float bottleYSpeed = 0.0f;

	bool upThrow = false;
	bool isExplosion = false;

public:
	FireBottle();
	~FireBottle() override;
	void Initialize(Model* model, const Vector3& position, Vector3 move, uint32_t team) override;

	void Update(float speed) override;
	void DeadUpdate() override;

	void Draw() override;

	void OnCollision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(bottleObj_->wtf.matWorld); };

	bool IsDead() override;
	void Dead() { isDead = true; }
	void SetDeathTime(uint32_t DeathTime) { DEATH_TIME = DeathTime; }

	void SetBullModel(Model* model) { Bullet::bulletModel_ = model; }
	void SetLength(float length) { vecLength = length; }

	//コライダー
public:
	void SetSphere(SphereCollider* sphere_) { sphere = sphere_; }
	SphereCollider* GetSphere() { return sphere; }
private:
	//int SPHERE_COLLISION_NUM;	//コライダー（スフィア）の数
	//std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	SphereCollider* sphere;
	//Ray* ray;
	Vector3 spherePos;
	Object3d* colliderPosTest_;
};
