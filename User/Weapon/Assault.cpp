/**
 * @file Assault.cpp
 * @brief
 */
#include "Assault.h"


Assault::Assault() {
}
Assault::~Assault() {
	delete model_;
}

/// 更新を行う
bool Assault::Initialize() {
	model_ = Model::LoadFromOBJ("sphere");
	goShot = true;
	return true;
}

/// 更新を行う
void Assault::Update(Input* input, bool isSlow) {

	_isSlow = isSlow;
	if (input) {

	}
	if (isSlow == true) {
		speed_ = nomalSpeed * _slowSpeed;
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
			if (_isSlow == true) {
				roadingTime = 150;
				goShot = false;
				mag = 0;
			}
			else {
				roadingTime = 50;
				goShot = false;
				mag = 0;
			}
		}
	}
	if (coolTime > 0) {
		coolTime--;
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
void Assault::Shot(Transform& shooter, Transform& reticle, uint32_t team) {

	if (coolTime <= 0 && goShot == true) {
		//弾を生成し、初期化
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
		Vector3 startPos, reticleVec, moveVec, velo;
		startPos = Affin::GetWorldTrans(shooter.matWorld); // 発射座標
		reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
		velo = reticleVec - startPos;
		velo.nomalize();
		moveVec = velo * speed_;
		moveVec.nomalize();
		newBullet->Initialize(model_, startPos + velo, moveVec, team);
		newBullet->SetDeathTime(200);

		//弾を登録
		BulletManager::GetInstance()->AddBullet(std::move(newBullet));
		mag++;

		//クールタイムをリセット
		if (team == PLAYER) {
			coolTime = 10;
		}if (team == ENEMY) {
			if (_isSlow == true) {
				coolTime = 40 * 5;
			}
			else {
				coolTime = 10 * 5;
			}
		}
	}
}