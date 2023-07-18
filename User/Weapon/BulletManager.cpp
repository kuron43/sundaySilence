#include "BulletManager.h"

float BulletManager::speed_ = 1.5f;

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
void BulletManager::Draw() {
	for (Bullet* bullet : bullets)
	{
		bullet->Draw();

	}
}