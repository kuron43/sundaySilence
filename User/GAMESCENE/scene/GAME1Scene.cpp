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
	_controller->_camera->SetEye(camposEye);
	_controller->_camera->SetTarget(camposTar);
	_controller->_camera->Update();
	_objects->player->Update(input);

	if (input->KeyboardTrigger(DIK_NUMPAD1)) {
		_controller->PushScene(new PauseScene(_controller, _objects));
	}
	else if (input->KeyboardTrigger(DIK_RETURN)) {
		_controller->ChangeScene(new EndScene(_controller, _objects));
	}
	else if (input->KeyboardTrigger(DIK_RETURN)) {
		_controller->ChangeScene(new EndScene(_controller, _objects));
	}
}

void GAME1Scene::Draw() {
	_objects->player->Draw(_controller->_dxCommon);
}