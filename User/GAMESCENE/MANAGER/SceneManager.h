#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4828)
#include <memory>
#include <stack>
#include <stdio.h>

#pragma warning(pop)

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

	// 各シーンのInitializeを呼び出す
	void SceneInitialize();
	// 各シーンのUpdateを呼び出す
	void SceneUpdate(Input* input);
	// 各シーンのDrawを呼び出す
	void SceneDraw();

	// シーンを変更する
	void SetSceneNum(uint32_t num) { sceneNum = num; isChange = true; };
	uint32_t GetSceneNum() { return sceneNum; };
	void ChangeScene();

	void PushScene(IScene*);
	void PopScene();
public:
	bool isChange = false;
	uint32_t sceneNum = 0;
	bool goToTitle = false;
};

//	参照元
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d <-やり方わからん