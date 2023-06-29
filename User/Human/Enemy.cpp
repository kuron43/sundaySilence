#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
}

///
void Enemy::Initialize() {
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
	weapon_->Update(input, isSlow);
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {
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

/// リセットを行う
void Enemy::Reset() {

}