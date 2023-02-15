#pragma once

#include "DirectXCommon.h"
#include "Input.h"
//#include "Audio.h"
//
//#include <string>
//#include <DirectXMath.h>
//
//#include "Object3d.h"
//#include "SpriteCommon.h"
//#include "Sprite.h"
//#include "Model.h"
//
//#include "Matrix4.h"
//#include "ConvertXM.h"
//#include "Transform.h"
//#include "DebugCamera.h"
//#include "FBX/FBXObject3d.h"
//#include "FBX/FbxLoader.h"
//#include "Particle/ParticleManager.h"


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
	
private: // メンバ変数

};

