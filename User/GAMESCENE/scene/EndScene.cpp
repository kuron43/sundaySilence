/**
 * @file EndScene.cpp
 * @brief
 */
#include "EndScene.h"
#include "SceneManager.h"

#include "TitleScene.h"

EndScene::EndScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
EndScene::~EndScene() {


}

void EndScene::Initialize() {
	end_ = std::make_unique<Sprite>();
	end_->Initialize(_objects->spriteCommon_.get(), 3);
	end_->SetSize({ 256,128 });
	end_->SetPozition({ (WinApp::window_width / 2) - 150,WinApp::window_height - 300 });
	_objects->player->Reset();
}

void EndScene::Update(Input* input) {
	end_->Update();

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->SetSceneNum(SCE_TITLE);
	}
}

void EndScene::Draw() {
	end_->Draw();

}