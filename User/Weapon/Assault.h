#pragma once
#include "Weapon.h"
#include "Bullet.h"

class Assault :
    public Weapon
{
private:
	std::list<std::unique_ptr<Bullet>> bullets_;
	Model* model_;
	bool active_ = false;

private:
	const float nomalSpeed = 1.5f;
	float speed_ = nomalSpeed;
	int coolTime = 3;
	int mag = 30;
	int roadingTime = 50;


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
	void Shot(Transform& player, Transform& reticle) override;
};

