#pragma once
/**
 * @file GameOverScene.h
 * @brief
 */
#include "IScene.h"
#include "SceneIntegrate.h"

class GameOver :
	public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	GameOver(SceneManager* controller, SceneObjects* objects);
	~GameOver() override;

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
	// カメラ座標
	Vector3 camposEye = { 0.0f,100.0f,-0.1f };
	Vector3 camposTar = { 0,0,0 };
	std::unique_ptr <Sprite> end_;
public:
	//代入演算子削除
	GameOver& operator=(const GameOver&) = delete;

	//コピーコンストラクタ削除
	GameOver(const GameOver&) = delete;
};