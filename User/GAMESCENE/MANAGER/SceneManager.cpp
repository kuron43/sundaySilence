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
	if (goToTitle == true) {
		_scene.pop();
		_scene.pop();
		_scene.emplace(new TitleScene(&*this, _objects));
		SceneInitialize();
		TransScene();
		goToTitle = false;
	}

	if (isChange == true && goToTitle == false) {

		switch (sceneNum)
		{
		case SCE_TITLE:
			_scene.pop();
			_scene.emplace(new TitleScene(&*this, _objects));
			SceneInitialize();
			TransScene();
			break;
		case SCE_GAME1:
			_scene.pop();
			_scene.emplace(new GAME1Scene(&*this, _objects));
			SceneInitialize();
			TransScene();
			break;

		case SCE_GAME2:
			_scene.pop();
			_scene.emplace(new GAME2Scene(&*this, _objects));
			SceneInitialize();
			TransScene();
			break;

		case SCE_OVER:
			_scene.pop();
			_scene.emplace(new EndScene(&*this, _objects));
			SceneInitialize();
			TransScene();
			break;
		case SCE_SELECT:
			_scene.pop();
			_scene.emplace(new SelectScene(&*this, _objects));
			SceneInitialize();
			TransScene();
			break;
		case SCE_PAUSE:
			Pause();
			break;
			/////////////////////////////////////////////////////
		case 0:
		default:
			break;
		}
		isChange = false;
	}
	else {
		isChange = false;
	}
}

void SceneManager::TransScene()
{
	_scene.emplace(new TransitionsScene(&*this, _objects));
	SceneInitialize();
}

void SceneManager::Pause()
{
	_scene.emplace(new PauseScene(&*this, _objects));
	SceneInitialize();
}

void SceneManager::PushScene(IScene* scene) {
	_scene.emplace(scene);
}
void SceneManager::PopScene() {
	_scene.pop();
	assert(!_scene.empty());
}