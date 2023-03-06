#pragma once
#include <memory>
#include <stack>

class Input;
class Scene;
class DirectXCommon;

// シーン管理クラス
class SceneManager
{
private:
	std::shared_ptr<Scene> _scene;
	DirectXCommon* _dxCommon;
public:

	SceneManager(DirectXCommon* dxCommon);
	~SceneManager();	

	// 各シーンのInitializeを呼び出す
	void SceneInitialize();
	// 各シーンのUpdateを呼び出す
	void SceneUpdate(Input* input);
	// 各シーンのDrawを呼び出す
	void SceneDraw();

	// シーンを変更する
	void ChangeScene(Scene*);

};

//	参照元
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d <-やり方わからん