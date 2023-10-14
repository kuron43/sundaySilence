#pragma once
#include "IScene.h"

class PauseScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	PauseScene(SceneManager* controller, SceneObjects* objects);
	~PauseScene() override;

	//void Cleate(SceneManager& controller) override;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力管理クラス</param>
	void Update(Input* input) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;


private:
	std::unique_ptr <Sprite> pauseGray;
public:


};

