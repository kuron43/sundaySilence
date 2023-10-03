#include "BulletManager.h"

float BulletManager::speed_ = 1.0f;

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}

void BulletManager::Update() {

	for (Bullet* bullet : bullets)
	{
		bullet->Update(speed_);

	}

}
void BulletManager::DeadUpdate() {

	for (Bullet* bullet : bullets)
	{
		bullet->DeadUpdate();
	}
}
void BulletManager::Draw() {
	for (Bullet* bullet : bullets)
	{
		bullet->Draw();

	}
}