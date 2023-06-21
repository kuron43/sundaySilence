#pragma once
#include "Weapon.h"
#include "Bullet.h"

class Assault :
    public Weapon
{
private:
	std::vector<Bullet> bullet;
	bool active_ = false;



public:
	Assault();
	~Assault();

	/// 更新を行う
	void Initialize() override;

	/// 更新を行う
	void Update(Input* input, bool isSlow) override;

	/// 描画を行う
	void Draw(DirectXCommon* dxCommon) override;

	/// リセットを行う
	void Reset() override;
};

