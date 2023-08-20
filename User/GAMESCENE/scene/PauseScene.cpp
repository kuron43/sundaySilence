#include "PauseScene.h"
#include "SceneManager.h"
#include "SceneIntegrate.h"

PauseScene::PauseScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;

	pauseGray = std::make_unique<Sprite>();
	pauseGray->Initialize(_objects->spriteCommon_.get(), 5);
	pauseGray->SetSize({ WinApp::window_width,WinApp::window_height });
	pauseGray->SetPozition({ 0,0 });
}
PauseScene::~PauseScene() {


}

void PauseScene::Initialize() {
	
}

void PauseScene::Update(Input* input) {
	pauseGray->Update();

	if (input->KeyboardTrigger(DIK_NUMPAD2)) {

		for (Wall* walls : _objects->walls) {
			walls->Reset();
		}
		for (Enemy* enemy : _objects->enemys) {
			enemy->Reset();
		}
		for (Boss* boss : _objects->boss) {
			boss->Reset();
		}
		BulletManager::GetInstance()->AllClearBullet();
		_objects->walls.clear();
		_objects->enemys.clear();
		_objects->boss.clear();

		_controller->goToTitle = true;
		_controller->PopScene();
	}else if (input->KeyboardTrigger(DIK_NUMPAD1) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->PopScene();
	}
}

void PauseScene::Draw() {

	_objects->player->Draw(_controller->_dxCommon);
	for (Enemy* enemy : _objects->enemys) {
		enemy->Draw(_controller->_dxCommon);
	}
	for (Boss* boss : _objects->boss) {
		boss->Draw(_controller->_dxCommon);
	}
	for (Wall* walls : _objects->walls) {
		walls->Draw(_controller->_dxCommon);
	}

	Object3d::PreDraw(_controller->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();

	pauseGray->Draw();
}