/**
 * @file Shotgun.cpp
 * @brief
 */
#include "Shotgun.h"

Shotgun::Shotgun() {
	
}
Shotgun::~Shotgun() {

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
	//model_ = Model::LoadFromOBJ("cube");
	return true;
}

/// 更新を行う
void Shotgun::Update(Input* input, bool isSlow) {
	if (isSlow) {
		speed_ = nomalSpeed / 2;
	}
	else
	{
		speed_ = nomalSpeed;
	}
	if (input->MouseButtonPush(0)) {
		
	}

	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update(speed_);
	}
}

/// 描画を行う
void Shotgun::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Draw();
	}
	Object3d::PostDraw();
}

/// リセットを行う
void Shotgun::Reset() {

}

// 発射を行う
void Shotgun::Shot(Transform& player, Transform& reticle, uint32_t team) {
	model_ = Model::LoadFromOBJ("cube");
	if (mag < 30) {
		if (coolTime <= 0) {
			//弾を生成し、初期化
			std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
			Vector3 startPos, reticleVec, moveVec, velo;
			startPos = Affin::GetWorldTrans(player.matWorld); // 発射座標
			reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
			velo = startPos - reticleVec;
			velo.nomalize();
			moveVec = velo * speed_;
			moveVec.nomalize();
			newBullet->Initialize(model_,startPos, moveVec,team);

			//弾を登録
			bullets_.push_back(std::move(newBullet));
			mag++;

			//クールタイムをリセット
			coolTime = 3;
		}
		else {
			coolTime--;
		}
	}
	if (mag >= 30) {
		roadingTime = 50;
		mag = 0;
	}
}