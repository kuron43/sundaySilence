/**
 * @file Shotgun.cpp
 * @brief
 */
#include "Shotgun.h"

Shotgun::Shotgun() {

}
Shotgun::~Shotgun() {
	delete model_;
}

Shotgun* Shotgun::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Shotgun* instans = new Shotgun();
	if (instans == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instans->Initialize()) {
		delete instans;
		assert(0);
		return nullptr;
	}

	return instans;
}

/// 更新を行う
bool Shotgun::Initialize() {
	model_ = Model::LoadFromOBJ("sphere");
	goShot = true;
	nowRoading = false;
	mag = 0;
	return true;
}

/// 更新を行う
void Shotgun::Update(Input* input/*, bool isSlow*/) {

	if (input) {

	}
	if (_isSlow == true) {
		speed_ = nomalSpeed * _slowSpeed;
	}
	else
	{
		speed_ = nomalSpeed;
	}
	// 
	if (mag < 5000 && nowRoading == false) {
		goShot = true;
	}
	else if (mag >= 5000 && nowRoading == false) {
		goShot = false;
		nowRoading = true;

		if (_isSlow == true) {
			mag = 0;
			roadingTime = 150*2;
		}
		else {
			mag = 0;
			roadingTime = 50*2;
		}

	}

	if (roadingTime < 0) {
		nowRoading = false;
	}
	roadingTime--;



	if (coolTime > 0) {
		coolTime--;
	}



	BulletManager::GetInstance()->SetSpeed(speed_);
}

/// 描画を行う
void Shotgun::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	Object3d::PostDraw();
}

/// リセットを行う
void Shotgun::Reset() {

}

// 発射を行う
void Shotgun::Shot(Transform& player, Transform& reticle, uint32_t team) {

	if (coolTime <= 0 && goShot == true) {
		for (uint32_t i = 0; i < 3; i++) {
			//弾を生成し、初期化
			std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
			Vector3 startPos, reticleVec, moveVec, velo;
			startPos = Affin::GetWorldTrans(player.matWorld); // 発射座標
			reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
			velo = reticleVec - startPos;
			if (i == 0) {
				velo = reticleVec - startPos;
			}
			else if (i == 1) {
				velo = Affin::VecMat(reticleVec - startPos, Affin::matRotateY(Affin::radConvert(3)));
			}
			else if (i == 2) {
				velo = Affin::VecMat(reticleVec - startPos, Affin::matRotateY(Affin::radConvert(-3)));
			}
			velo.nomalize();
			moveVec = velo * speed_;
			moveVec.nomalize();
			newBullet->Initialize(model_, startPos + velo, moveVec, team);
			newBullet->SetDeathTime(20);

			//弾を登録
			BulletManager::GetInstance()->AddBullet(std::move(newBullet));
		}
		mag++;

		//クールタイムをリセット
		if (team == PLAYER) {
			coolTime = 15 * 3;
		}if (team == ENEMY) {
			if (_isSlow == true) {
				coolTime = (15 * 3) * 5;
			}
			else {
				coolTime = 15 * 5;
			}
		}
	}
}