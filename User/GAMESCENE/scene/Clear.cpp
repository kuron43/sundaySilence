/**
 * @file Clear.cpp
 * @brief
 */
#include "SceneIntegrate.h"
#include "SceneManager.h"

Clear::Clear(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
Clear::~Clear() {


}

void Clear::Initialize() {
	clearSP_ = std::make_unique<Sprite>();
	clearSP_->Initialize(_objects->spriteCommon_.get(), 4);
	clearSP_->SetSize({ 256.0f,128.0f });
	clearSP_->SetPozition({ (WinApp::window_width / 2.0f) - 128.0f,100.0f });
	{
		titleButton_ = std::make_unique<Sprite>();
		titleButton_->Initialize(_objects->spriteCommon_.get(), 10);
		titleButton_->SetSize({ 300.0f,300.0f });
		titleButton_->SetPozition({ (WinApp::window_width / 2) - 150,WinApp::window_height - 300 });
	}
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->player->Reset();
}

void Clear::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();

	clearSP_->Update();
	titleButton_->Update();
	_objects->mouseCursor_->Update(input);	
	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get()) && input->MouseButtonTrigger(0)) {
		_controller->SetSceneNum(SCE_TITLE);
	}
}

void Clear::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);

	clearSP_->Draw();
	titleButton_->Draw();
	_objects->mouseCursor_->Draw();
}