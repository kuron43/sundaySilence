#include "SceneIntegrate.h"



TitleScene::TitleScene(SceneManager* controller) {
	_controller = controller;
}
TitleScene::~TitleScene() {

}

void TitleScene::Initialize(DirectXCommon* dxCommon, Camera* camera) {
	
}

void TitleScene::Update(Input* input, Camera* camera) {

	Vector3 a = { 0,0,0 };

	_controller->bossFbxO_->Update();

	
	{

		if (input->KeyboardTrigger(DIK_0)) {
			_controller->bossFbxO_->PlayAnimation(0);
		}
		if (input->KeyboardTrigger(DIK_1)) {
			_controller->bossFbxO_->PlayAnimation(1);
		}
		if (input->KeyboardTrigger(DIK_2)) {
			_controller->bossFbxO_->PlayAnimation(2);
		}
		if (input->KeyboardTrigger(DIK_3)) {
			_controller->bossFbxO_->PlayAnimation(3);
		}
		if (input->KeyboardTrigger(DIK_4)) {
			_controller->bossFbxO_->PlayAnimation(4);
		}
		if (input->KeyboardTrigger(DIK_5)) {
			_controller->bossFbxO_->PlayAnimation(5);
		}
		if (input->KeyboardTrigger(DIK_6)) {
			_controller->bossFbxO_->PlayAnimation(6);
		}
		if (input->KeyboardTrigger(DIK_7)) {
			_controller->bossFbxO_->PlayAnimation(7);
		}
	}

	if (input->KeyboardTrigger(DIK_RETURN)) {
		_controller->ChangeScene(new GAME1Scene(_controller));
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon) {

	_controller->bossFbxO_->Draw(dxCommon->GetCommandList());
}
