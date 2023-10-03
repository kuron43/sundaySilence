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
	_objects->mouseCursor_->Update(input);

	title_->Update();

	_objects->bossFbxO_->Update();
	_objects->player->Update(input,true);
	
	

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}else if (input->KeyboardTrigger(DIK_SPACE)) {
		_controller->SetSceneNum(SCE_SELECT);
	}

	
}

void TitleScene::Draw() {
	
	title_->Draw();

	_objects->player->Draw(_controller->_dxCommon);
	_objects->mouseCursor_->Draw(_controller->_dxCommon);
}

