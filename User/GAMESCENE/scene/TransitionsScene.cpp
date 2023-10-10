#include "TransitionsScene.h"
#include "Easing.h"
#include "Affin.h"


TransitionsScene::TransitionsScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
TransitionsScene::~TransitionsScene() {


}

void TransitionsScene::Initialize() {
	transSP_ = std::make_unique<Sprite>();
	transSP_->Initialize(_objects->spriteCommon_.get(), 36);
	transSP_->SetSize({ WinApp::window_width/2.0f ,WinApp::window_height/2.0f });
	transSPpos_ = { WinApp::window_width / 2 - transSP_->GetSize().x / 2,WinApp::window_height / 3.5f };
	transSPscale_ = Vector3(0.5f, 0.5f, 0.5f);
	transSP_->SetPozition(transSPpos_);
	transSP_->SetScale(transSPscale_);

	titleSP_ = std::make_unique<Sprite>();
	titleSP_->Initialize(_objects->spriteCommon_.get(), 11);
	titleSP_->SetSize({ 600,300 });
	titleSPpos_ = { WinApp::window_width / 2.0f - 300.0f,-300.0f };
	titleSP_->SetPozition(titleSPpos_);
}

void TransitionsScene::Update(Input* input) {
	if (input) {

	}
	sceneTimer++;
	time++;
	easetime = (float)time / easeMaxTime;
	if (!on) {
		transSPscale_ = Easing::OutQuintVec3(Vector3(0.5f, 0.5f, 0.5f), Vector3(2, 2, 2), (float)easetime);
		transSPpos_ = Easing::OutQuintVec2(Vector2(WinApp::window_width / 2 - transSP_->GetSize().x / 2, WinApp::window_height / 3.5f), Vector2(0.0f, 0.0f), (float)easetime);
		titleSPpos_.y =(float)Easing::OutQuintFloat(-300.0f, WinApp::window_height / 2.0f - 150.0f, (float)easetime);
	}
	else {
		titleSPpos_.y = (float)Easing::InQuintFloat(WinApp::window_height / 2.0f - 150.0f, -300.0f, (float)easetime);
	}
	transSP_->SetScale(transSPscale_);
	transSP_->SetPozition(transSPpos_);
	titleSP_->SetPozition(titleSPpos_);
	transSP_->Update();
	titleSP_->Update();
	if (time >= easeMaxTime) {
		time = 0;
		on = true;
	}

	if (sceneTimer >= easeMaxTime * (uint32_t)2) {
		_controller->PopScene();
	}
}

void TransitionsScene::Draw() {
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

	//////////////////////

	transSP_->Draw();
	titleSP_->Draw();
}