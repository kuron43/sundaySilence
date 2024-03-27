#pragma once
/**
 * @file TitleScene.h
 * @brief
 */
#include "IScene.h"
#include "JsonLoader.h"
#include "SceneIntegrate.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;
	SceneObjects* _objects;
public:

	TitleScene(SceneManager* controller, SceneObjects* objects);
	~TitleScene() override;

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
	//代入演算子削除
	TitleScene& operator=(const TitleScene&) = delete;
	//コピーコンストラクタ削除
	TitleScene(const TitleScene&) = delete;

	Vector3 camposEye = { 0.0f,40.0f,-90.01f };
	Vector3 camposTar = { 0,0,0 };

	float forcalLengs = 30.0f;
	std::unique_ptr <ParticleManager>  particle_;
public:

private://リソース
	std::unique_ptr <Sprite> title_;
	Vector2 titlePos = { 20.0f,10.0f };
	std::unique_ptr <Sprite> titleButton_;
	std::unique_ptr <Sprite> red_;

	uint32_t titleTime_ = 0;
	float sinMoveTitle = 0.0f;
};