#include "GameScene.h"

#pragma warning(push)
#pragma warning(disable: 4514)

#include<sstream>
#include<fstream>
#include<iomanip>
#include <imgui.h>
#pragma warning(pop)

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
	CollisionManager::GetInstance()->Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	dxCommon_ = dxCommon;
	input_ = input;

	collisionManager_ = CollisionManager::GetInstance();

	//FBX
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneObjects = std::make_unique<SceneObjects>(dxCommon);
	sceneObjects->Initialize();

	sceneManager = new SceneManager(dxCommon, camera, sceneObjects.get());
	sceneManager->SceneInitialize();

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	sceneManager->ChangeScene();

	//particleManager_->Update();

	sceneObjects->lightGroup->Update();
	sceneObjects->skydome_O->Update();
	sceneObjects->UpdateImGui();

	sceneManager->SceneUpdate(input_);


	collisionManager_->CheckAllCollisions();
	camera->Update();
#ifdef _DEBUG
	// Imgui
	float forcalL = camera->GetForcalLengs();
	ImGui::Begin("ForcalLengs");
	ImGui::SliderFloat("forcalLengs", &forcalL,0.01f,120.0f);
	ImGui::End();
	camera->SetFocalLengs(forcalL);
#endif
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	Object3d::PreDraw(dxCommon_->GetCommandList());
	sceneObjects->skydome_O->Draw();
	Object3d::PostDraw();
	sceneManager->SceneDraw();
	//particleManager_->Draw();p

	/*ImGui::Begin("Info");
	ImGui::Text("E : particle");
	ImGui::Text("WASD : ball rotate");
	ImGui::End();*/
}

void GameScene::DrawUI()
{

}
