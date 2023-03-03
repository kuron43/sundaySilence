#include "EndScene.h"
#include "SceneManager.h"
#include "DirectXCommon.h"
#include "Input.h"

#include "TitleScene.h"

EndScene::EndScene() {

}
EndScene::EndScene(SceneManager* controller) {
	_controller = controller;
}
EndScene::~EndScene() {

}

void EndScene::Initialize(DirectXCommon* dxCommon) {

}
void EndScene::Update(Input* input) {
	if (input->TriggerKey(DIK_SPACE)) {
		_controller->ChangeScene(new TitleScene(_controller));
	}
}
void EndScene::Draw(DirectXCommon* dxCommon) {

}