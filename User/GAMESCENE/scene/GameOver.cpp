/**
 * @file EndScene.cpp
 * @brief
 */
#include "SceneIntegrate.h"
#include "SceneManager.h"

GameOver::GameOver(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
GameOver::~GameOver() {


}

void GameOver::Initialize() {
	end_ = std::make_unique<Sprite>();
	end_->Initialize(_objects->spriteCommon_.get(), 10);
	end_->SetSize({ 300.0f,300.0f });
	end_->SetPozition({ (WinApp::window_width / 2) - 150,WinApp::window_height - 300 });
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->player->Reset();
}

void GameOver::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();

	end_->Update();
	_objects->mouseCursor_->Update(input);	
	if (_objects->mouseCursor_->Cursor2Sprite(end_.get()) && input->MouseButtonTrigger(0)) {
		_controller->SetSceneNum(SCE_TITLE);
	}
}

void GameOver::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);

	//for (Enemy* enemy : _objects->enemys) {
	//	enemy->Draw(_controller->_dxCommon);
	//}
	//for (Boss* boss : _objects->boss) {
	//	boss->Draw(_controller->_dxCommon);
	//}
	//for (Wall* walls : _objects->walls) {
	//	walls->Draw(_controller->_dxCommon);
	//}
	//_objects->player->Draw(_controller->_dxCommon);

	end_->Draw();
	_objects->mouseCursor_->Draw();
}