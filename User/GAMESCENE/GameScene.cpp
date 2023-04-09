#include "GameScene.h"

#include<sstream>
#include<iomanip>
#include"imgui.h"

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

	cam_TF.Initialize();
	cam_TF.position = { 0.0f, 3.0f, -8.0f };
	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	ParticleManager_2::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneManager = new SceneManager(dxCommon);
	sceneManager->SceneInitialize();	

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	if (input->KeyboardPush(DIK_UP)) {
		cam_TF.position.y += 1;
	}
	if (input->KeyboardPush(DIK_DOWN)) {
		cam_TF.position.y -= 1;
	}
	if (input->KeyboardPush(DIK_LEFT)) {
		cam_TF.position.x -= 1;
	}
	if (input->KeyboardPush(DIK_RIGHT)) {
		cam_TF.position.x += 1;
	}
	cam_TF.UpdateMat();
	camera->SetEye(cam_TF.position);
	camera->Update();
	/*if (input->Pad_X_ButtonInput(B)) {
		input->Pad_X_ShakeController(1.0f, 10);
	}*/
	sceneManager->SceneUpdate(input);

}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	sceneManager->SceneDraw();

	ImGui::Begin("Info");
	ImGui::Text("E : particle");
	ImGui::Text("arrowkey : camera");
	ImGui::End();
}