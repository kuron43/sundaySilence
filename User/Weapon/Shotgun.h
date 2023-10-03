#pragma once
#include "Weapon.h"
#include "Bullet.h"

class Shotgun :
    public Weapon
{
private:
	std::list<std::unique_ptr<Bullet>> bullets_;
	Model* model_;
	bool active_ = false;
	const uint32_t WeaponNum = 2;

private:
	const float nomalSpeed = 1.5f;
	float speed_ = nomalSpeed;
	uint32_t coolTime = 3;
	uint32_t mag = 5;
	uint32_t roadingTime = 500;


public:
	Shotgun();
	~Shotgun();

	static Shotgun* Create();
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
};


