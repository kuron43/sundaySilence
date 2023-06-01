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

	this->dxCommon = dxCommon;
	this->input = input;

	cam_TF.Initialize();
	cam_TF.position = { 0.0f, 2.5f, 8.0f };
	tar = { 0.0f, 2.5f, 0.0f };


	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneManager = new SceneManager(dxCommon, camera);
	sceneManager->ObjectInitialize();
	sceneManager->SceneInitialize();
	// Json
	{
		//leveData = JsonLoader::LoadJsonFile("Test");

		//// モデル読み込み
		//modelcube = Model::LoadFromOBJ("cube");
		//modelREX = Model::LoadFromOBJ("REX");

		//models.insert(std::make_pair("cube", modelcube));
		//models.insert(std::make_pair("REX", modelREX));

		//{


		//	for (auto& objectData : leveData->objects) {
		//		//ファイル名から登録済みモデルを検索
		//		Model* model = nullptr;
		//		decltype(models)::iterator it = models.find(objectData.fileName);
		//		if (it != models.end()) { model = it->second; }
		//		// 座標
		//		Object3d* newObject = Object3d::Create();
		//		newObject->SetModel(model);
		//		//座標
		//		Vector3 pos;
		//		pos = objectData.translation;
		//		newObject->wtf.position = pos;
		//		//回転
		//		Vector3 rot;
		//		rot = objectData.rotation;
		//		newObject->wtf.rotation = rot;
		//		//拡縮
		//		Vector3 sca;
		//		sca = objectData.scaling;
		//		newObject->wtf.scale = sca;
		//		//
		//		objects.push_back(newObject);

		//	}
		//}
	}

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	cam_TF.UpdateMat();
	camera->SetEye(Affin::GetWorldTrans(cam_TF.matWorld));
	camera->SetTarget(tar);
	camera->Update();

	

	/*for (auto& object : objects) {
		object->Update();
	}*/
	sceneManager->SceneUpdate(input);
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	sceneManager->SceneDraw();
	// Json
	{
		/*Object3d::PreDraw(dxCommon->GetCommandList());
		for (auto& object : objects) {
			object->Draw();
		}
		Object3d::PostDraw();*/
	}
	//ImGui::Begin("Info");
	////ImGui::Text("E : particle");
	//ImGui::Text("WASD : ball rotate");
	//ImGui::End();
}