#include "GameScene.h"


#include<sstream>
#include<fstream>
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
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	dxCommon_ = dxCommon;
	input_ = input;

	collisionManager_ = CollisionManager::GetInstance();
	bulletManager_ = BulletManager::GetInstance();

	cam_TF.Initialize();
	cam_TF.position = { 100.0f, 100, -0.01f };
	tar = { 100.0f, 0.0f, 0.0f };
	//FBX	(テスト)
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneObjects = std::make_unique<SceneObjects>(dxCommon, camera);
	sceneObjects->Initialize();

	sceneManager = new SceneManager(dxCommon, camera, sceneObjects.get());
	sceneManager->SceneInitialize();

	// Json
	{
		//leveData = JsonLoader::LoadJsonFile("gameOne");

		//// モデル読み込み
		//modelcube = Model::LoadFromOBJ("cube");
		////modelREX = Model::LoadFromOBJ("REX");

		//jsonModels.insert(std::make_pair("cube", modelcube));
		////jsonModels.insert(std::make_pair("REX", modelREX));

		//{


		//	for (auto& objectData : leveData->JsonObjects) {
		//		//ファイル名から登録済みモデルを検索
		//		Model* model = nullptr;
		//		decltype(jsonModels)::iterator it = jsonModels.find(objectData.fileName);
		//		if (it != jsonModels.end()) { model = it->second; }
		//		// 座標
		//		Object3d* newObject = Object3d::Create();
		//		newObject->SetModel(model);
		//		//座標
		//		Vector3 pos;
		//		pos = objectData.translation;
		//		newObject->wtf.m_Pos = pos;
		//		//回転
		//		Vector3 rot;
		//		rot = objectData.rotation;
		//		newObject->wtf.rotation = rot;
		//		//拡縮
		//		Vector3 sca;
		//		sca = objectData.scaling;
		//		newObject->wtf.scale = sca;
		//		//

		//		if (objectData.fileName == "cube") {
		//			pos+= Vector3(11,11,11);
		//		}
		//		JsonObjects.push_back(newObject);

		//	}
		//}
	}

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	collisionManager_->CheckAllCollisions();

	/*cam_TF.UpdateMat();
	camera->SetEye(Affin::GetWorldTrans(cam_TF.matWorld));
	camera->SetTarget(tar);	*/
	{// JSON
		/*for (auto& object : JsonObjects) {
			object->Update();
		}*/
	}
	sceneObjects->lightGroup->Update();
	sceneManager->SceneUpdate(input_);
	bulletManager_->DeadUpdate();

	camera->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	sceneManager->SceneDraw();
	// Json
	{
		/*Object3d::PreDraw(dxCommon->GetCommandList());
		for (auto& object : JsonObjects) {
			object->Draw();
		}
		Object3d::PostDraw();*/
	}

	/*ImGui::Begin("Info");
	ImGui::Text("E : particle");
	ImGui::Text("WASD : ball rotate");
	ImGui::End();*/
}