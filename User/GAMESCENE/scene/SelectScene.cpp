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


	selectTitele_ = std::make_unique<Sprite>();
	selectTitele_->Initialize(_objects->spriteCommon_.get(), 5);
	selectTitele_->SetSize({ 256,128 });
	selectTitele_->SetPozition({ 200,100 });

	stage1_ = std::make_unique<Sprite>();
	stage1_->Initialize(_objects->spriteCommon_.get(), 5);
	stage1_->SetSize({ 300,300 });
	stage1_->SetPozition({ (WinApp::window_width / 2)-150,WinApp::window_height - 300 });

	left_ = std::make_unique<Sprite>();
	left_->Initialize(_objects->spriteCommon_.get(), 26);
	left_->SetSize({ 100,300 });
	left_->SetPozition({ (WinApp::window_width / 2) - 350,WinApp::window_height - 300 });

	right_ = std::make_unique<Sprite>();
	right_->Initialize(_objects->spriteCommon_.get(), 28);
	right_->SetSize({ 100,300 });
	right_->SetPozition({ (WinApp::window_width / 2) + 250,WinApp::window_height - 300 });
}

void SelectScene::Update(Input* input) {
	selectTitele_->Update();
	stage1_->Update();
	left_->Update();
	right_->Update();
	_objects->mouseCursor_->Update(input);
	

	SelectSceneNum(input);
	MoveScene();

	if (selectNum == 0) {
		stage1_->SetTextureIndex(10);
	}
	else if (selectNum == 1) {
		stage1_->SetTextureIndex(20);
	}
	else if (selectNum == 2) {
		stage1_->SetTextureIndex(21);
	}
	if (_objects->mouseCursor_->Cursor2Sprite(left_.get())) {
		left_->SetTextureIndex(27);
	}
	else {
		left_->SetTextureIndex(26);
	}
	if (_objects->mouseCursor_->Cursor2Sprite(right_.get())) {
		right_->SetTextureIndex(29);
	}
	else {
		right_->SetTextureIndex(28);
	}

	ImGui::Begin("SELECT NUM");
	ImGui::Text("SelectNum : %d", selectNum);
	ImGui::End();
}

void SelectScene::Draw() {
	selectTitele_->Draw();
	stage1_->Draw();
	left_->Draw();
	right_->Draw();

	_objects->mouseCursor_->Draw();
}
void SelectScene::SelectSceneNum(Input* input) {
	if (selectNum == 0) {
		if (_objects->mouseCursor_->Cursor2Sprite(left_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 2;
		}
		else if (_objects->mouseCursor_->Cursor2Sprite(right_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 1;
		}
	}
	else if (selectNum == 1) {
		if (_objects->mouseCursor_->Cursor2Sprite(left_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 0;
		}
		else if (_objects->mouseCursor_->Cursor2Sprite(right_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 2;
		}
	}
	else if (selectNum == 2) {
		if (_objects->mouseCursor_->Cursor2Sprite(left_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 1;
		}
		else if (_objects->mouseCursor_->Cursor2Sprite(right_.get()) && input->MouseButtonTrigger(0)) {
			selectNum = 0;
		}
	}
	if (_objects->mouseCursor_->Cursor2Sprite(stage1_.get()) && input->MouseButtonTrigger(0)) {
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