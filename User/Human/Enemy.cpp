#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
	delete weapon_;
}

///
void Enemy::Initialize() {
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();
	weapon_ = new Assault();
	weapon_->Initialize();

}

///
void Enemy::Update(Input* input, bool isTitle) {
	assert(input);
	object_->Update();
	if (input->KeyboardPush(DIK_SPACE)) {
		weapon_->Shot(object_->wtf, reticle->wtf);
	}
	if (isTitle) {
		weapon_->Update(input, isSlow);
	}
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {

	if (!isDead) {
		Object3d::PreDraw(dxCommon->GetCommandList());
		object_->Draw();
		if (nowTitle) {
			reticle->Draw();
		}
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
}

/// リセットを行う
void Enemy::Reset() {

}