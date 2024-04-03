#pragma once
/**
 * @file GAME2Scene.h
 * @brief ゲーム実行2ステージ目
 */
#include "IScene.h"

#include "JsonLoader.h"
#include "SceneIntegrate.h"

class GAME2Scene :
	public IScene
{
public:
	GAME2Scene();
	~GAME2Scene() override;

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
	bool startTime_ = false;
	bool stageClear = false;
	bool stageFailed = false;

	// カメラ座標
	Vector3 camposEye = { 0.0f,90.0f,-10.0001f };
	Vector3 camposTar = { 0,0,0 };
	float forcalLengs = 30.0f;
};

