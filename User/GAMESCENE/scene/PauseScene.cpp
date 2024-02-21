/**
 * @file PauseScene.cpp
 * @brief
 */
#include "PauseScene.h"
#include "SceneManager.h"
#include "SceneIntegrate.h"

PauseScene::PauseScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
PauseScene::~PauseScene() {


}

void PauseScene::Initialize() {
	pauseGray_ = std::make_unique<Sprite>();
	pauseGray_->Initialize(_objects->spriteCommon_.get(), 6);
	pauseGray_->SetSize({ WinApp::window_width,WinApp::window_height });
	pauseGray_->SetPozition({ 0,0 });
	{
		pauseGoBuck_ = std::make_unique<Sprite>();
		pauseGoBuck_->Initialize(_objects->spriteCommon_.get(), 52);
		pauseGoBuck_->SetSize({ 256,128 });
		pauseGoBuck_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.9f + 135.0f });
	}
	{
		titleButton_ = std::make_unique<Sprite>();
		titleButton_->Initialize(_objects->spriteCommon_.get(), 50);
		titleButton_->SetSize({ 256,128 });
		titleButton_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.9f });
	}
}

void PauseScene::Update(Input* input) {
	pauseGray_->Update();
	_objects->mouseCursor_->Update(input);

	pauseGoBuck_->Update();
	titleButton_->Update();

	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get())) {

		if (input->MouseButtonTrigger(0)) {
			BulletManager::GetInstance()->AllClearBullet();
			_objects->walls.clear();
			_objects->enemys.clear();
			_objects->boss.clear();

			_controller->goToTitle = true;
		}
		titleButton_->SetTextureIndex(51);
	}
	else {
		titleButton_->SetTextureIndex(50);
	}
	if (input->KeyboardTrigger(DIK_TAB) ) {
		_controller->PopScene();
	}
	else if (_objects->mouseCursor_->Cursor2Sprite(pauseGoBuck_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_controller->PopScene();
		}
	}
}

void PauseScene::Draw() {
	_objects->floorGround->Draw(_controller->_dxCommon);
	_objects->player->Draw(_controller->_dxCommon);
	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (std::unique_ptr <Wall>& walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}

	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	_objects->UIDraw();
	// ポーズシーンのぐれー
	pauseGray_->Draw();
	//ここより下にポーズシーン用の描画処理
	titleButton_->Draw();
	pauseGoBuck_->Draw();


	_objects->mouseCursor_->Draw();
}