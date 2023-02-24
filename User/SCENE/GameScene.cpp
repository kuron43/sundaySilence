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
	delete sprite;
	delete camera;

	delete skydome, skydomeMD;
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

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	//ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	skydomeMD = Model::LoadFromOBJ("skydome");

	skydome = Object3d::Create();

	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome->Update();
	

	sprite = new Sprite();

	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition(spritePOS);
	sprite->SetSize(Vector2{ WinApp::window_width/3,WinApp::window_height/3 });

	spriteCommon->LoadTexture(0, "inu.png");
	sprite->SetTextureIndex(0);
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	skydome->Update();




}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	
	skydome->Draw();
	
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	sprite->Draw();
}