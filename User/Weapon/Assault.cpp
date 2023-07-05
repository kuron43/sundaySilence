#include "Assault.h"


Assault::Assault() {
	//model_ = Model::LoadFromOBJ("cube");
}
Assault::~Assault() {

}

Assault* Assault::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Assault* instans = new Assault();
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
bool Assault::Initialize() {
	model_ = Model::LoadFromOBJ("cube");
	return true;
}

/// 更新を行う
void Assault::Update(Input* input, bool isSlow) {
	assert(input);
	isSlow_ = isSlow;
	if (input) {

	}
	if (isSlow) {
		speed_ = nomalSpeed / 2;
	}
	else
	{
		speed_ = nomalSpeed;
	}
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update(speed_);
	}
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->IsDead(); });
}

/// 描画を行う
void Assault::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		if (bullet->IsDead() == false) {
			bullet->Draw();
		}
	}
	Object3d::PostDraw();
}

/// リセットを行う
void Assault::Reset() {

}

// 発射を行う
void Assault::Shot(Transform& player, Transform& reticle,int team) {
	if (roadingTime <= 0) {
		if (mag < 30) {
			if (coolTime <= 0) {
				//弾を生成し、初期化
				std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
				Vector3 startPos, reticleVec, moveVec, velo;
				startPos = Affin::GetWorldTrans(player.matWorld); // 発射座標
				reticleVec = Affin::GetWorldTrans(reticle.matWorld);	// レティクルの3D座標
				velo = reticleVec - startPos;
				velo.nomalize();
				moveVec = velo * speed_;
				moveVec.nomalize();
				newBullet->Initialize(model_, startPos, moveVec,team);

				//弾を登録
				bullets_.push_back(std::move(newBullet));
				mag++;

				//クールタイムをリセット
				if (isSlow_ == true) {
					coolTime = 9;
				}
				else {
					coolTime = 3;
				}
			}
			else {
				coolTime--;
			}
		}
		if (mag >= 30) {
			if (isSlow_ == true) {
				roadingTime = 150;
			}
			else {
				roadingTime = 50;
			}
			mag = 0;
		}
	}
	roadingTime--;

}