#include "GameScene.h"

/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {

}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	//オーディオ解放
	//audio->Finalize();
	//delete audio;

	delete spriteCommon;
	delete camera;
	delete sceneManager;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input){
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneManager = new SceneManager(dxCommon);
	sceneManager->SceneInitialize();	

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	camera->Update();
	if (input->Pad_X_ButtonInput(RB)) {
		input->Pad_X_ShakeController(1.0f, 10);
	}
	sceneManager->SceneUpdate(input);

}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	sceneManager->SceneDraw();

}