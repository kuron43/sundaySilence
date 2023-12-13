/**
 * @file BulletManager.cpp
 * @brief
 */
#include "BulletManager.h"

float BulletManager::speed_ = 0.8f;

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}

void BulletManager::Update() {

	//デスフラグの立った弾を削除
	bullets.remove_if([](std::unique_ptr<Bullet>& bullet) {
		bullet->DeadUpdate();
		return bullet->IsDead();
		});
	//弾の更新
	for (std::unique_ptr<Bullet>& bullet : bullets)
	{
		bullet->Update(speed_);

	}
}

void BulletManager::Draw() {
	for (std::unique_ptr<Bullet>& bullet : bullets)
	{
		bullet->Draw();
	}
}
