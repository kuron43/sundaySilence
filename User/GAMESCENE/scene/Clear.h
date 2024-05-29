#pragma once
/**
 * @file Clear.h
 * @brief
 */
#include "IScene.h"
#include "SceneIntegrate.h"

class Clear :
	public IScene
{
public:
	Clear();
	~Clear() override;

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
	// カメラ座標
	Vector3 camposEye = { 0.0f,100.0f,-0.1f };
	Vector3 camposTar = { 0,0,0 };
	std::unique_ptr <Sprite> clearSP_;
	std::unique_ptr <Sprite> titleButton_;
	std::unique_ptr <Sprite> selectButton_;
public:
	//代入演算子削除
	Clear& operator=(const Clear&) = delete;

	//コピーコンストラクタ削除
	Clear(const Clear&) = delete;
};