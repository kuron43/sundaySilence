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

}

///
void Enemy::Update(Input* input) {
	assert(input);
	object_->Update();
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void Enemy::Reset() {

}