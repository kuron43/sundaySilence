#include "BossManager.h"
#include "Boss.h"

void BossManager::Update(uint32_t pattNum)
{
	patNum_ = pattNum;
	//switch (patNum_)
	//{

	//case 0: // 待機
	//	if (boss_->isDead == false) {

	//		boss_->bossFbxO_->AnimRotPlay();
	//		boss_->bossFbxO_->PlayAnimation(0);
	//	}
	//	break;

	//case 1: // 移動
	//	if (boss_->isDead == false) {

	//		boss_->bossFbxO_->AnimRotPlay();
	//		boss_->bossFbxO_->PlayAnimation(2);
	//		boss_->object_->wtf.position.x += 0.1f;
	//	}
	//	break;

	//case 2:	// 攻撃
	//	if (boss_->isFire == true && boss_->isDead == false) {
	//		boss_->bossFbxO_->AnimRotPlay();
	//		boss_->bossFbxO_->PlayAnimation(4);
	//		boss_->isFireOld = true;
	//		boss_->weapon_->Shot(boss_->object_->wtf, boss_->reticle->wtf, ENEMY);
	//	}
	//	break;
	//}
}
