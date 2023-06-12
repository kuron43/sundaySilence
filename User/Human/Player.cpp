#include "Player.h"


Player::Player() {

}
Player::~Player() {
	delete model_;
}

/// シーンの更新を行う
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

}

/// シーンの更新を行う
void Player::Update(Input* input) {

	object_->Update();
}

/// シーンの描画を行う
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}