#pragma once
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

class Bullet
{
public:
	int team_;
	int weapon;
	bool isTeam;
	bool isDead;

	const int deathTime = 50;
	int timeCount;
	
	Object3d* bulletObj_;
	static Model* bulletModel_;

	Vector3 moveVec;

public:
	Bullet();
	~Bullet();
	void Initialize(Model* model,const Vector3& position, Vector3 move,int team);

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

