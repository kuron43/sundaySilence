#include "BossManager.h"
#include "Boss.h"

void BossManager::Update(uint32_t pattNum)
{
	patNum_ = pattNum;
	switch (patNum_)
	{

	case 0: // 待機
		if (boss_->isDead == false) {

			boss_->bossFbxO_->AnimIsRotateChange(false);
			boss_->bossFbxO_->PlayAnimation(0);
		}
		break;

	case 1: // 移動
		if (boss_->isDead == false) {

			boss_->bossFbxO_->AnimIsRotateChange(false);
			boss_->bossFbxO_->PlayAnimation(3);
		}
		break;

	case 2:	// 攻撃
		if (boss_->isFire == true && boss_->isDead == false) {
			if (!isPlayAnim) {
				boss_->bossFbxO_->AnimIsRotateChange(false);
				boss_->bossFbxO_->PlayAnimation(4);
				isPlayAnim = true;
			}
			else if(isPlayAnim){
				boss_->bossFbxO_->AnimIsRotateChange(false);
				boss_->bossFbxO_->PlayAnimation(5);
				boss_->weapon_->Shot(boss_->object_->transForm, boss_->reticle->transForm, Team::ENEMY);
				isPlayAnim = false;
			}
		}
		break;
	}



	//-----animationUpdate-----//
	if (isPlayAnim == true) {
		int32_t maxFlame = 30;

		animFlameCT++;

		if (animFlameCT >= maxFlame) {
			animFlameCT = 0;
		}

		//boss_->bossFbxO_->AnimFlameInter(animFlameCT, maxFlame);

	}
	else {
		int32_t maxFlame = 30;

		animFlameCT++;
		if (animFlameCT >= maxFlame) {
			animFlameCT = 0;
		}

		//boss_->bossFbxO_->AnimFlameInter(animFlameCT, maxFlame);
	}
}
