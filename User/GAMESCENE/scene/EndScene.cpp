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

}

void EndScene::Update(Input* input) {

	if (input->KeyboardTrigger(DIK_RETURN) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new TitleScene(_controller,_objects));
	}
}

void EndScene::Draw() {


}