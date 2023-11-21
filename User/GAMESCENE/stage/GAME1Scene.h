#pragma once
/**
 * @file GAME1Scene.h
 * @brief ゲーム実行１ステージ目
 */
#include "IScene.h"

#include "JsonLoader.h"
#include "SceneIntegrate.h"


class GAME1Scene :
    public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:
	GAME1Scene(SceneManager* controller, SceneObjects* objects);
	~GAME1Scene() override;

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
	bool startTime_ = false;
	bool stageClear = false;
	bool stageFailed = false;
	uint32_t randTime_;

	// カメラ座標
	Vector3 camposEye = { 16.0f,90.0f,-10.0001f };
	Vector3 camposTar = { 16,0,0 };


	uint32_t testTime = 0;

public:
	LevelData* leveData = nullptr;
};

