#pragma once
/**
 * @file PauseScene.h
 * @brief
 */
#include "IScene.h"

class PauseScene :
    public IScene
{
protected:
	SceneManager* _manager;
	SceneObjects* _objects;
public:
	PauseScene(SceneManager* manager, SceneObjects* objects);
	~PauseScene() override;

	//void Cleate(SceneManager& manager) override;
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
	std::unique_ptr <Sprite> pauseGray_;
	std::unique_ptr <Sprite> pauseGoBuck_;
	std::unique_ptr <Sprite> titleButton_;
public:


};

