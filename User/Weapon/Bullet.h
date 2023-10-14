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
	bool isTeam;
	bool isDead;

	const uint32_t deathTime = 120;
	uint32_t timeCount;
	
	Object3d* bulletObj_;
	static Model* bulletModel_;

	Vector3 moveVec;

public:
	Bullet();
	~Bullet();
	void Initialize(Model* model,const Vector3& position, Vector3 move, uint32_t team);

	void Update(float speed);
	void DeadUpdate();

	void Draw();

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(bulletObj_->wtf.matWorld); };

	bool IsDead() const { return isDead; }
	void Dead() { isDead = true; }

	void SetBullModel(Model* model) { Bullet::bulletModel_ = model; }

	//コライダー
public:
	void SetSphere(SphereCollider* sphere_) { sphere = sphere_; }
	SphereCollider* GetSphere() { return sphere; }
private:
	//int SPHERE_COLISSION_NUM;	//コライダー（スフィア）の数
	//std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	SphereCollider* sphere;
	//Ray* ray;
	Vector3 spherePos;
	Object3d* coliderPosTest_;
};

