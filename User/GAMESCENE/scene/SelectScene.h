#pragma once
/**
 * @file SelectScene.h
 * @brief
 */
#include "IScene.h"
#include "SceneIntegrate.h"

class SelectScene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	SelectScene(SceneManager* controller, SceneObjects* objects);
	~SelectScene() override;

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

	void SelectSceneNum(Input* input);
	void MoveScene();

private:
	std::unique_ptr <Sprite> selectTitele_;
	std::unique_ptr <Sprite> stage1_;
	std::unique_ptr <Sprite> left_;
	std::unique_ptr <Sprite> right_;

	uint32_t selectNum;
	uint32_t resultNum;
	bool isConfirm = false;

public:

};

