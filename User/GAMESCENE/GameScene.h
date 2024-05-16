#pragma once

#pragma warning(push)
#pragma warning(disable: 4514)

#include<string>
#pragma warning(pop)

#include "DirectXCommon.h"
#include "Input.h"
#include "SpriteCommon.h"
#include "SceneManager.h"
#include "SceneObjects.h"
#include "SceneFactory.h"
#include "IScene.h"
#include "Affin.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "BulletManager.h"
#include "JsonLoader.h"
#include "ObjectParticle.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
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

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

public:


private: // メンバ変数 (固定)
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;
	// mane-ja-
	SceneManager* sceneManager = nullptr;
	SceneFactory* sceneFactory = nullptr;
	CollisionManager* collisionManager_ = nullptr;
	BulletManager* bulletManager_ = nullptr;
	ObjParticleManager* objParticleManager_ = nullptr;
	//ParticleManager* particleManager_ = nullptr;

private:	//メンバ変数
	std::unique_ptr<SceneObjects> sceneObjects;

};

