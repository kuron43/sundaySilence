#include "GAME1Scene.h"
#include "SceneManager.h"

#include "SceneIntegrate.h"


GAME1Scene::GAME1Scene(SceneManager* controller, SceneObjects* objects) {
	_controller = controller;
	_objects = objects;
}

GAME1Scene::~GAME1Scene() {
}

void GAME1Scene::Initialize() {
}

void GAME1Scene::Update(Input* input) {

	if (input->KeyboardTrigger(DIK_RETURN) || input->Pad_X_ButtonTrigger(LB)) {
		_controller->ChangeScene(new TitleScene(_controller, _objects));
	}
}

void GAME1Scene::Draw() {

}