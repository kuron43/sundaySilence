#include "Player.h"


Player::Player() {

}
Player::~Player() {
	delete model_;
}

///
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

}

///
void Player::Update(Input* input) {
	Move(input);
	object_->Update();
}

///
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void Player::Reset() {

}

void Player::Move(Input* input) {
	
	float speed = kMoveSpeed_;
	if (input->KeyboardPush(DIK_R)) {
		isSlow = true;
	}
	if (input->KeyboardPush(DIK_T)) {
		isSlow = false;
	}

	if (isSlow == true) {
		speed = speed * 0.25f;
	}
	else {
		speed = kMoveSpeed_;
	}

	if (input->KeyboardPush(DIK_D)) {
		velocity_.x += speed;
	}
	if (input->KeyboardPush(DIK_A)) {
		velocity_.x -= speed;
	}
	if (input->KeyboardPush(DIK_W)) {
		velocity_.z += speed;
	}
	if (input->KeyboardPush(DIK_S)) {
		velocity_.z -= speed;
	}
	

	object_->wtf.position = velocity_;

}