#pragma once
#include "Weapon.h"
#include "Bullet.h"

class Assault :
    public Weapon
{
private:
	std::list<Bullet*> bullets_;
	Model* model_;
	bool active_ = false;
	const int WeaponNum = 1;

	int team_;

private:
	const float nomalSpeed = 1.5f;
	float speed_ = nomalSpeed;
	int coolTime = 0;
	int mag = 0;
	int roadingTime = 0;
	bool goShot;


public:
	Assault();
	~Assault();

	static Assault* Create();
	/// 更新を行う
	bool Initialize() override;

	/// 更新を行う
	void Update(Input* input, bool isSlow) override;

	/// 描画を行う
	void Draw(DirectXCommon* dxCommon) override;

	/// リセットを行う
	void Reset() override;

	// 発射を行う
	void Shot(Transform& player, Transform& reticle,int team) override;
};

