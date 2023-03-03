#pragma once


class Input;
class SceneManager;
class DirectXCommon;

// シーン管理のための基底クラス
// (純粋基底クラス)

class Scene
{
protected:

	SceneManager* _controller;

public:

	Scene();
	virtual ~Scene();

	//virtual Scene Create(SceneManager& controller) = 0;
	/// シーンの更新を行う
	virtual void Initialize(DirectXCommon* dxCommon) = 0;

	/// シーンの更新を行う
	virtual void Update(Input* input) = 0;

	/// シーンの描画を行う
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

