#pragma once

#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "SpriteCommon.h"
#include "SceneManager.h"
#include "SceneObjects.h"
#include "Affin.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "BulletManager.h"

#include "JsonLoader.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // 静的メンバ変数
	//static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:

	
private: // メンバ変数 (固定)
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;
	// mane-ja-
	SceneManager* sceneManager = nullptr;
	CollisionManager* collisionManager_ = nullptr;
	BulletManager* bulletManager_ = nullptr;

private:	//メンバ変数
	std::unique_ptr<SceneObjects> sceneObjects;

};

