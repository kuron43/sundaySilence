#include "SceneFactory.h"
#include "SceneIntegrate.h"

IScene* SceneFactory::CleateScene(const std::string& sceneName)
{
	IScene* newScene = nullptr;

	if (sceneName == "TITLE") {
		newScene = new TitleScene();
	}
	if (sceneName == "CLEAR") {
		newScene = new Clear();
	}
	if (sceneName == "PAUSE") {
		newScene = new PauseScene();
	}
	if (sceneName == "SELECT") {
		newScene = new SelectScene();
	}
	if (sceneName == "TRANS") {
		newScene = new TransitionsScene();
	}
	if (sceneName == "TUTREAL") {
		newScene = new GAME1Scene();
	}
	if (sceneName == "GAME") {
		newScene = new GAME2Scene();
	}

	return newScene;
}

//
//void SceneManager::ChangeScene() {
//	if (goToTitle == true) {
//		_scene.pop();
//		_scene.pop();
//		_scene.emplace(new TitleScene());
//		_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TITLE]).get());
//		SceneInitialize();
//		_objects->OFFIsUIDraw();
//		TransScene();
//		goToTitle = false;
//	}
//
//	if (isChange == true && goToTitle == false) {
//
//		switch (sceneNum)
//		{
//		case SCE_TITLE:
//			_scene.pop();
//			_scene.emplace(new TitleScene());
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TITLE]).get());
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_GAME1:
//			_scene.pop();
//			_scene.emplace(new GAME1Scene());
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TUTRIAL]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//
//		case SCE_GAME2:
//			_scene.pop();
//			_scene.emplace(new GAME2Scene());
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE1]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//		case SCE_GAME3:
//			_scene.pop();
//			_scene.emplace(new GAME2Scene());
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE2]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//
//		case SCE_OVER:
//			_scene.pop();
//			_scene.emplace(new EndScene());
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_SELECT:
//			_scene.pop();
//			_scene.emplace(new SelectScene());
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_CLEAR:
//			_scene.pop();
//			_scene.emplace(new Clear());
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_PAUSE:
//			Pause();
//			break;
//			/////////////////////////////////////////////////////
//		case 0:
//		default:
//			break;
//		}
//		isChange = false;
//	}
//	else {
//		isChange = false;
//	}
//}
//
//void SceneManager::TransScene()
//{
//	_scene.emplace(new TransitionsScene());
//	SceneInitialize();
//}
//
//void SceneManager::Pause()
//{
//	_scene.emplace(new PauseScene());
//	SceneInitialize();
//}
//
//void SceneManager::PushScene(IScene* scene) {
//	_scene.emplace(scene);
//}
//void SceneManager::PopScene() {
//	_scene.pop();
//	assert(!_scene.empty());
//}