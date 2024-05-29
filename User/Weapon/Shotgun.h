/**
 * @file Shotgun.h
 * @brief
 */
#pragma once
#include "Weapon.h"
#include "Bullet.h"

// ショットガン
class Shotgun :
    public Weapon
{
private:
	bool active_ = false;
	bool goShot;
	bool nowRoading;
	bool PADDING[5];
	Model* model_;
	const uint32_t WeaponNum = 2;

private:
	const float nomalSpeed = 1.5f;
	float speed_ = nomalSpeed;
	int32_t coolTime = 3;
	int32_t mag = 5;
	int32_t roadingTime = 500;


public:
	Shotgun();
	~Shotgun();

	static Shotgun* Create();
	/// 更新を行う
	bool Initialize() override;

	/// 更新を行う
	void Update(Input* input) override;

	/// 描画を行う
	void Draw(DirectXCommon* dxCommon) override;

	/// リセットを行う
	void Reset() override;

	// 発射を行う
	void Shot(Transform& player, Transform& reticle, uint32_t team) override;
};


