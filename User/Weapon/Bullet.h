#pragma once
#include "Object3d.h"

class Bullet
{
public:
	int tribe;
	int weapon;
	bool isTeam;
	bool isDead;

	
	std::unique_ptr<Object3d> bulletObj_;
	static Model* bulletModel_;

	Vector3 moveVec;

public:
	Bullet();
	~Bullet();
	void Initialize(Model* model,const Vector3& position, Vector3 move);

	void Update(float speed);

	void Draw();

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(bulletObj_->wtf.matWorld); };

	bool IsDead() const { return isDead; }

	void SetBullModel(Model* model) { Bullet::bulletModel_ = model; }


};

