#include "SceneFactory.h"
#include "SceneIntegrate.h"

Iscene* SceneFactory::CleateScene(const std::string& sceneName)
{
	IScene* newScene = nullptr;

	if (sceneName == "TITLE") {
		newScene = new TitleScene();
	}


	return newScene;
}

//
//void SceneManager::ChangeScene() {
//	if (goToTitle == true) {
//		_scene.pop();
//		_scene.pop();
//		_scene.emplace(new TitleScene(&*this, _objects));
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
//			_scene.emplace(new TitleScene(&*this, _objects));
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TITLE]).get());
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_GAME1:
//			_scene.pop();
//			_scene.emplace(new GAME1Scene(&*this, _objects));
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TUTRIAL]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//
//		case SCE_GAME2:
//			_scene.pop();
//			_scene.emplace(new GAME2Scene(&*this, _objects));
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE1]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//		case SCE_GAME3:
//			_scene.pop();
//			_scene.emplace(new GAME2Scene(&*this, _objects));
//			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE2]).get());
//			SceneInitialize();
//			_objects->ONIsUIDraw();
//			TransScene();
//			break;
//
//		case SCE_OVER:
//			_scene.pop();
//			_scene.emplace(new EndScene(&*this, _objects));
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_SELECT:
//			_scene.pop();
//			_scene.emplace(new SelectScene(&*this, _objects));
//			SceneInitialize();
//			_objects->OFFIsUIDraw();
//			TransScene();
//			break;
//		case SCE_CLEAR:
//			_scene.pop();
//			_scene.emplace(new Clear(&*this, _objects));
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
//	_scene.emplace(new TransitionsScene(&*this, _objects));
//	SceneInitialize();
//}
//
//void SceneManager::Pause()
//{
//	_scene.emplace(new PauseScene(&*this, _objects));
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