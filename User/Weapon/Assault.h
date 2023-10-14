#pragma once
/**
 * @file Assault.h
 * @brief
 */
#include "Weapon.h"
#include "Bullet.h"

// アサルトライフル
class Assault :
    public Weapon
{
private:
	std::list<Bullet*> bullets_;
	Model* model_;
	const uint32_t WeaponNum = 1;
	uint32_t team_;


private:
	const float nomalSpeed = 1.0f;
	float speed_ = nomalSpeed;
	uint32_t coolTime = 0;
	uint32_t mag = 0;
	uint32_t roadingTime = 0;

	bool active_ = false;
	bool goShot;
	uint16_t padding;

public:
	Assault();
	~Assault();

	//static Assault* Create();
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

private:

	//代入演算子削除
	Assault& operator=(const Assault&) = delete;

	//コピーコンストラクタ削除
	Assault(const Assault&) = delete;
};

