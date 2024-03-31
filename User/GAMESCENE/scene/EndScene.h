#pragma once
/**
 * @file EndScene.h
 * @brief 
 */
#include "IScene.h"
#include "SceneIntegrate.h"

class EndScene :
    public IScene
{
protected:
	SceneManager* _manager;
	SceneObjects* _objects;
public:
	EndScene(SceneManager* manager, SceneObjects* objects);
	~EndScene() override;

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
	std::unique_ptr <Sprite> end_;
public:
	//代入演算子削除
	EndScene& operator=(const EndScene&) = delete;

	//コピーコンストラクタ削除
	EndScene(const EndScene&) = delete;
};