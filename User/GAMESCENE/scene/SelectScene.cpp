#include "SelectScene.h"
#include "SceneManager.h"

SelectScene::SelectScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
SelectScene::~SelectScene() {


}

void SelectScene::Initialize() {

	selectNum = 0;
	resultNum = 0;
	isConfirm = false;


	titele_ = std::make_unique<Sprite>();
	titele_->Initialize(_objects->spriteCommon_.get(), 3);
	titele_->SetSize({ 256,128 });
	titele_->SetPozition({ 200,100 });
}

void SelectScene::Update(Input* input) {
	titele_->Update();

	SelectSceneNum(input);
	MoveScene();


	ImGui::Begin("SELECT NUM");
	ImGui::Text("SelectNum : %d", selectNum);
	ImGui::End();
}

void SelectScene::Draw() {
	titele_->Draw();

}
void SelectScene::SelectSceneNum(Input* input) {
	if (selectNum == 0) {
		if (input->KeyboardTrigger(DIK_LEFT) || input->Pad_X_ButtonTrigger(LB)) {
			selectNum = 2;
		}
		else if (input->KeyboardTrigger(DIK_RIGHT) || input->Pad_X_ButtonTrigger(RB)) {
			selectNum = 1;
		}
	}
	else if (selectNum == 1) {
		if (input->KeyboardTrigger(DIK_LEFT) || input->Pad_X_ButtonTrigger(LB)) {
			selectNum = 0;
		}
		else if (input->KeyboardTrigger(DIK_RIGHT) || input->Pad_X_ButtonTrigger(RB)) {
			selectNum = 2;
		}
	}
	else if (selectNum == 2) {
		if (input->KeyboardTrigger(DIK_LEFT) || input->Pad_X_ButtonTrigger(LB)) {
			selectNum = 1;
		}
		else if (input->KeyboardTrigger(DIK_RIGHT) || input->Pad_X_ButtonTrigger(RB)) {
			selectNum = 0;
		}
	}
	if (input->KeyboardTrigger(DIK_RETURN)) {
		resultNum = selectNum;
		isConfirm = true;
	}
}
void SelectScene::MoveScene() {
	if (isConfirm == true) {
		switch (resultNum)
		{
		case 0:
			_controller->SetSceneNum(SCE_TITLE);
			break;
		case 1:
			_controller->SetSceneNum(SCE_GAME1);
			break;
		case 2:
			_controller->SetSceneNum(SCE_GAME2);
			break;
		}
	}
	else {

	}
}