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
	SceneManager* sceneManager = nullptr;
	std::unique_ptr<SceneObjects> sceneObjects;

	// json
	Model* modelcube = nullptr;
	//Model* modelREX = nullptr;

	LevelData* leveData = nullptr;
	std::map<std::string, Model*> jsonModels;
	std::vector<Object3d*> JsonObjects;

	CollisionManager* collisionManager_ = nullptr;


private:	//メンバ変数
	Transform cam_TF;
	Vector3 eye = { 0.0f, 10.0f, -10.0f };
	Vector3 tar = { 0.0f, 0.0f, 0.0f };


};

