#pragma once
/**
 * @file SceneManager.h
 * @brief シーン管理クラス
 */
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#include <memory>
#include <stack>
#include <stdio.h>

#pragma warning(pop)

#include "ISceneFactory.h"

class Input;
class IScene;
class DirectXCommon;
class Camera;
class SceneObjects;

// シーン管理クラス
class SceneManager
{
public:
	std::stack<std::shared_ptr<IScene>> _scene;
	DirectXCommon* _dxCommon;
	Camera* _camera;
	SceneObjects* _objects;
	
public:

	SceneManager(DirectXCommon* dxCommon, Camera* camera, SceneObjects* objects);
	~SceneManager();
	void Initialize();

	// 各シーンのInitializeを呼び出す
	void SceneInitialize();
	// 各シーンのUpdateを呼び出す
	void SceneUpdate(Input* input);
	// 各シーンのDrawを呼び出す
	void SceneDraw();

	// シーンを変更する
	void ChangeScene();
	void SetSceneNum(uint32_t num) { sceneNum = num; isChange = true; };
	uint32_t GetSceneNum() { return sceneNum; };
	void PushScene(IScene*);
	void PopScene();

	// 
	void TransScene();
	void Pause();

public:
	uint32_t sceneNum = 0;
	bool isChange = false;
	bool goToTitle = false;
	uint16_t PADDING;
};

//	基本構成の参照元
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d 