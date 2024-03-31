/**
 * @file Clear.cpp
 * @brief
 */
#include "SceneIntegrate.h"
#include "SceneManager.h"

Clear::Clear(SceneManager* manager, SceneObjects* objects) {
	_manager = manager;
	_objects = objects;
}
Clear::~Clear() {


}

void Clear::Initialize() {
	clearSP_ = std::make_unique<Sprite>();
	clearSP_->Initialize(_objects->spriteCommon_.get(), 4);
	clearSP_->SetSize({ 512.0f,256.0f });
	clearSP_->SetPozition({ (WinApp::window_width / 2.0f) - 256.0f,100.0f });
	{
		titleButton_ = std::make_unique<Sprite>();
		titleButton_->Initialize(_objects->spriteCommon_.get(), 50);
		titleButton_->SetSize({ 256.0f,128.0f });
		titleButton_->SetPozition({ (WinApp::window_width / 2) - 128,WinApp::window_height - 275 });
	}
	{
		selectButton_ = std::make_unique<Sprite>();
		selectButton_->Initialize(_objects->spriteCommon_.get(), 53);
		selectButton_->SetSize({ 256.0f,128.0f });
		selectButton_->SetPozition({ (WinApp::window_width / 2) - 128,WinApp::window_height - 135 });
	}
	_manager->_camera->SetEye(camposEye);
	_manager->_camera->SetTarget(camposTar);
	_manager->_camera->Update();
	_objects->player->Reset();
}

void Clear::Update(Input* input) {
	_manager->_camera->SetEye(camposEye);
	_manager->_camera->SetTarget(camposTar);
	_manager->_camera->Update();

	_objects->mouseCursor_->Update(input);	
	clearSP_->Update();
	titleButton_->Update();
	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_manager->SetSceneNum(SCE_TITLE);
		}
		titleButton_->SetTextureIndex(51);
	}else {
		titleButton_->SetTextureIndex(50);
	}
	selectButton_->Update();
	if (_objects->mouseCursor_->Cursor2Sprite(selectButton_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_manager->SetSceneNum(SCE_SELECT);
		}
		selectButton_->SetTextureIndex(54);
	}
	else {
		selectButton_->SetTextureIndex(53);
	}
}

void Clear::Draw() {
	_objects->floorGround->Draw(_manager->_dxCommon);

	clearSP_->Draw();
	titleButton_->Draw();
	selectButton_->Draw();
	_objects->mouseCursor_->Draw();
}