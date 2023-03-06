#include "SceneManager.h"
#include "Input.h"
#include <cassert>
#include "DirectXCommon.h"

// シーンのインクルード
#include "TitleScene.h"
#include "GAME1Scene.h"
#include "EndScene.h"

SceneManager::SceneManager(DirectXCommon* dxCommon) {
	_dxCommon = dxCommon;
	_scene.reset(new TitleScene(&*this));

}
SceneManager::~SceneManager() {

}

void SceneManager::SceneInitialize() {
	_scene.get()->Initialize(_dxCommon);

}

void SceneManager::SceneUpdate(Input* input) {
	_scene.get()->Update(input);

}

void SceneManager::SceneDraw() {
	_scene.get()->Draw(_dxCommon);

}

void SceneManager::ChangeScene(Scene* scene) {
	_scene.reset(scene);
	SceneInitialize();

}