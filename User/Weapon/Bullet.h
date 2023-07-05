#pragma once
#include "Object3d.h"

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

	void Draw();

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(bulletObj_->wtf.matWorld); };

	bool IsDead() const { return isDead; }
	void Dead() { isDead = true; }

	void SetBullModel(Model* model) { Bullet::bulletModel_ = model; }


};

