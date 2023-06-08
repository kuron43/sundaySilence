#include "SceneManager.h"
#include "Input.h"
#include <cassert>
#include "DirectXCommon.h"
#include "Camera.h"
#include "SceneObjects.h"

// シーンのインクルード
#include "SceneIntegrate.h"


SceneManager::SceneManager(DirectXCommon* dxCommon, Camera* camera,SceneObjects* objects) {
	_dxCommon = dxCommon;
	_objects = objects;
	_scene.reset(new TitleScene(&*this,_objects));
	_camera = camera;

}
SceneManager::~SceneManager() {

}

void SceneManager::SceneInitialize() {
	_scene.get()->Initialize();

}

void SceneManager::SceneUpdate(Input* input) {


	_scene.get()->Update(input);
}

void SceneManager::SceneDraw() {
	_scene.get()->Draw();

}

void SceneManager::ChangeScene(IScene* scene) {
	_scene.reset(scene);
	SceneInitialize();

}