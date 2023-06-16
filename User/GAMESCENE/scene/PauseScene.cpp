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

}

void PauseScene::Update(Input* input) {

	if (input->KeyboardTrigger(DIK_NUMPAD9) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->PopScene();
	}
}

void PauseScene::Draw() {


}