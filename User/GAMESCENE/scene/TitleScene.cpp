#include "SceneIntegrate.h"



TitleScene::TitleScene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}
TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {
	title_ = std::make_unique<Sprite>();
	title_->Initialize(_objects->spriteCommon_.get(), 1);
	title_->SetSize({ 600,300 });
	title_->SetPozition(titlePos);
	titleButton_ = std::make_unique<Sprite>();
	titleButton_->Initialize(_objects->spriteCommon_.get(), 8);
	titleButton_->SetSize({ 256,128 });
	titleButton_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.5f });

	red_ = std::make_unique<Sprite>();
	red_->Initialize(_objects->spriteCommon_.get(), 8);
	red_->SetSize({ 24,24 });
	red_->SetPozition({ WinApp::window_width / 2.5f,WinApp::window_height / 1.5f });

	titleTime_ = 0;
	sinMoveTitle = 0.0f;
	titlePos = { 20,10 };
}

void TitleScene::Update(Input* input) {
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->mouseCursor_->Update(input);

	sinMoveTitle = 10 + sin(3.1415f / 2 / 120 * titleTime_) * 30;
	titleTime_++;
	titlePos.y = sinMoveTitle;
	title_->SetPozition(titlePos);

	title_->Update();
	titleButton_->Update();

	_objects->player->Update(input, true);

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	if (_objects->mouseCursor_->Cursor2Sprite(titleButton_.get())) {
		if (input->MouseButtonTrigger(0)) {
			_controller->SetSceneNum(SCE_SELECT);
		}
		titleButton_->SetTextureIndex(9);
	}
	else {
		titleButton_->SetTextureIndex(8);
	}

	//timeEnd = false;
	//if (isActive) {
	//	nowTime++;
	//	easetime = (float)nowTime / easeMaxTime;
	//	if (nowPointNum == 0 && nowTime <= easeMaxTime) {
	//		resultVec = Easing::InOutQuintVec3(startPos, points[0], (float)easetime);
	//		if (time == easeMaxTime - 1) {
	//			nowPointNum = 1;
	//			nowTime = 1;
	//			timeEnd = true;
	//		}
	//	}
	//}
}

void TitleScene::Draw() {
	title_->Draw();
	titleButton_->Draw();

	_objects->player->Draw(_controller->_dxCommon);
	_objects->mouseCursor_->Draw();
}



