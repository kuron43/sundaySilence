/**
 * @file IScene.cpp
 * @brief
 */
#include "IScene.h"
#include "SceneManager.h"
#include "SceneObjects.h"

SceneObjects* IScene::_objects = nullptr;
SceneManager* IScene::_manager = nullptr;

IScene::IScene() {
}
IScene::~IScene(){
}

