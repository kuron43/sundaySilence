#include "SceneManager.h"
#include "Input.h"
#include <cassert>
#include "DirectXCommon.h"
#include "Camera.h"
#include "SceneObjects.h"

// シーンのインクルード
#include "SceneIntegrate.h"


SceneManager::SceneManager(DirectXCommon* dxCommon, Camera* camera, SceneObjects* objects) {
	_dxCommon = dxCommon;
	_objects = objects;
	_scene.emplace(new TitleScene(&*this, _objects));
	_camera = camera;

}
SceneManager::~SceneManager() {

}

void SceneManager::SceneInitialize() {
	_scene.top().get()->Initialize();

}

void SceneManager::SceneUpdate(Input* input) {


	_scene.top().get()->Update(input);
}

void SceneManager::SceneDraw() {
	_scene.top().get()->Draw();

}

void SceneManager::ChangeScene() {

	if (isChange) {

		switch (sceneNum)
		{
		case SC_TITLE:
			_scene.pop();
			_scene.emplace(new TitleScene(&*this, _objects));
			SceneInitialize();
			break;
		case SC_GAME1:
			_scene.pop();
			_scene.emplace(new GAME1Scene(&*this, _objects));
			SceneInitialize();
			break;
		case SC_OVER:
			_scene.pop();
			_scene.emplace(new EndScene(&*this, _objects));
			SceneInitialize();
			break;
			/////////////////////////////////////////////////////
		case 0:
		default:
			break;
		}
		assert(_scene);
		isChange = false;
	}
	else {
		isChange = false;
	}
}

void SceneManager::PushScene(IScene* scene) {
	_scene.emplace(scene);
}
void SceneManager::PopScene() {
	_scene.pop();
	assert(!_scene.empty());
}