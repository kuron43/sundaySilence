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
	transSP_->Initialize(_objects->spriteCommon_.get(), 3);
	transSP_->SetSize({ 256,128 });
	transSP_->SetPozition({ 200,100 });
}

void TransitionsScene::Update(Input* input) {
	transSP_->Update();

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->SetSceneNum(SCE_TITLE);
	}
}

void TransitionsScene::Draw() {
	transSP_->Draw();

}