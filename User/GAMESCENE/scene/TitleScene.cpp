#include "SceneIntegrate.h"



TitleScene::TitleScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {
	title_ = std::make_unique<Sprite>();
	title_->Initialize(_objects->spriteCommon_.get(), 1);
	title_->SetSize({ 256,128 });
	title_->SetPozition({ 200,100 });
}

void TitleScene::Update(Input* input) {	
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();

	title_->Update();

	_objects->bossFbxO_->Update();
	_objects->player->Update(input,true);
	
	{
		//if (input->KeyboardTrigger(DIK_0)) {
		//	_objects->bossFbxO_->PlayAnimation(0);
		//}
		//if (input->KeyboardTrigger(DIK_1)) {
		//	_objects->bossFbxO_->PlayAnimation(1);
		//}
		//if (input->KeyboardTrigger(DIK_2)) {
		//	_objects->bossFbxO_->PlayAnimation(2);
		//}
		//if (input->KeyboardTrigger(DIK_3)) {
		//	_objects->bossFbxO_->PlayAnimation(3);
		//}
		//if (input->KeyboardTrigger(DIK_4)) {
		//	_objects->bossFbxO_->PlayAnimation(4);
		//}
		//if (input->KeyboardTrigger(DIK_5)) {
		//	_objects->bossFbxO_->PlayAnimation(5);
		//}
		//if (input->KeyboardTrigger(DIK_6)) {
		//	_objects->bossFbxO_->PlayAnimation(6);
		//}
		//if (input->KeyboardTrigger(DIK_7)) {
		//	_objects->bossFbxO_->PlayAnimation(7);
		//}
	}

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}else if (input->KeyboardTrigger(DIK_SPACE)) {
		_controller->ChangeScene(new GAME1Scene(_controller, _objects));
	}

	
}

void TitleScene::Draw() {
	
	title_->Draw();

	//_objects->bossFbxO_->Draw(_controller->_dxCommon->GetCommandList());
	_objects->player->Draw(_controller->_dxCommon);
}
