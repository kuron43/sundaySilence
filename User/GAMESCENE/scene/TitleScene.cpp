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
	titleButton_ = std::make_unique<Sprite>();
	titleButton_->Initialize(_objects->spriteCommon_.get(), 8);
	titleButton_->SetSize({ 256,128 });
	titleButton_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.5f });
}

void TitleScene::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->mouseCursor_->Update(input);

	title_->Update();
	titleButton_->Update();

	_objects->player->Update(input, true);



	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_controller->SetSceneNum(SCE_SELECT);
		}
		titleButton_->SetTextureIndex(9);
	}
	else {
		titleButton_->SetTextureIndex(8);
	}
}

void TitleScene::Draw() {
	title_->Draw();
	titleButton_->Draw();

	_objects->player->Draw(_controller->_dxCommon);
	_objects->mouseCursor_->Draw();
}



