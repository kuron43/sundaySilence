#pragma once

#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ParticleManager.h"

#include "Matrix4.h"
#include "Camera.h"


//#include "FBX/FBXObject3d.h"
//#include "FBX/FbxLoader.h"


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
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	
private: // メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;
	Audio* audio = nullptr;

	SceneManager* sceneManager = nullptr;

private:	//メンバ変数

};

