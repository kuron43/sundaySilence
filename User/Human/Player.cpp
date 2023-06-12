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
	Move(input);
	object_->Update();
}

/// シーンの描画を行う
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}

void Player::Move(Input* input) {
	if (input->KeyboardPush(DIK_D)) {
		object_->wtf.position.x += 1;
	}
	if (input->KeyboardPush(DIK_A)) {
		object_->wtf.position.x -= 1;
	}
	if (input->KeyboardPush(DIK_W)) {
		object_->wtf.position.z += 1;
	}
	if (input->KeyboardPush(DIK_S)) {
		object_->wtf.position.z -= 1;
	}
}