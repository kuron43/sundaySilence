/**
 * @file Assault.cpp
 * @brief
 */
#include "Assault.h"


Assault::Assault() {
}
Assault::~Assault() {
}

/// 更新を行う
bool Assault::Initialize() {
	model_ = Model::LoadFromOBJ("cube");
	goShot = true;
	return true;
}

/// 更新を行う
void Assault::Update(Input* input, bool isSlow) {
	
	isSlow_ = isSlow;
	if (input) {

	}
	if (isSlow == true) {
		speed_ = nomalSpeed / 2;
	}
	else
	{
		speed_ = nomalSpeed;
	}
	// 
	if (roadingTime <= 0) {
		if (mag < 10) {
			goShot = true;
		}
		if (mag >= 10) {
			if (isSlow_ == true) {
				roadingTime = 150;
				goShot = false;
			}
			else {
				roadingTime = 50;
				goShot = false;
			}
			mag = 0;
		}
	}
	roadingTime--;

	BulletManager::GetInstance()->SetSpeed(speed_);
}

/// 描画を行う
void Assault::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	Object3d::PostDraw();
}

/// リセットを行う
void Assault::Reset() {

}

// 発射を行う
void Assault::Shot(Transform& player, Transform& reticle, uint32_t team) {
	
	if (coolTime <= 0 && goShot == true) {
		//弾を生成し、初期化
		Bullet* newBullet = new Bullet();
		Vector3 startPos, reticleVec, moveVec, velo;
		startPos = Affin::GetWorldTrans(player.matWorld); // 発射座標
		reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
		velo = reticleVec - startPos;
		velo.nomalize();
		moveVec = velo * speed_;
		moveVec.nomalize();
		newBullet->Initialize(model_, startPos, moveVec, team);

		//弾を登録
		BulletManager::GetInstance()->AddBullet(std::move(newBullet));
		mag++;

		//クールタイムをリセット
		if (team == PLAYER) {
			if (isSlow_ == true) {
				coolTime = 45;
			}
			else {
				coolTime = 15;
			}
		}if (team == ENEMY) {
			if (isSlow_ == true) {
				coolTime = 45 * 3;
			}
			else {
				coolTime = 15 * 3;
			}
		}
	}
	else {
		coolTime--;
	}
}