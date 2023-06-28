#pragma once

#include "GameScene.h"
#include "PostEffect.h"
#include "fbxsdk.h"
#include "Framework.h"

class MyGame : public Framework
{
public:	// メンバ関数

	// 初期化
	void Initialize() override;
	// 終了
	void Finalize() override;
	// 毎フレーム更新
	void Update() override;
	// 描画
	void Draw() override;

protected:

	//ポインタ
	//FbxManager* fbxManager = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;
};

