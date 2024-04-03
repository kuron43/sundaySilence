#pragma once
/**
 * @file Bullet.h
 * @brief
 */
#include "Object3d.h"

#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

enum Team
{
	NONE = 0,
	PLAYER = 1,
	ENEMY = 2,
	
};

// 弾クラス
class Bullet
{
public:
	uint32_t team_;
	uint32_t weapon;

	uint32_t DEATH_TIME = 800;
	uint32_t timeCount;
	
	Object3d* bulletObj_;
	static Model* bulletModel_;

	Vector3 moveVec;

	bool isTeam;
	bool isDead;
	bool upThrow = false;
	bool isInversion = false;

public:
	Bullet();
	virtual ~Bullet();
	virtual void Initialize(Model* model,const Vector3& position, Vector3 move, uint32_t team);

	virtual void Update(float speed);
	virtual void DeadUpdate();

	virtual void Draw();

	void OnCollision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(bulletObj_->wtf.matWorld); };

	virtual bool IsDead();
	void Dead() { isDead = true; }
	void SetDeathTime(uint32_t DeathTime) { DEATH_TIME = DeathTime; }

	void SetBullModel(Model* model) { Bullet::bulletModel_ = model; }

	//コライダー
public:
	void SetSphere(SphereCollider* sphere_) { sphere = sphere_; }
	SphereCollider* GetSphere() { return sphere; }
private:
	SphereCollider* sphere;
	Vector3 spherePos;
	uint32_t PADDING;
	Object3d* colliderPosTest_;
};

