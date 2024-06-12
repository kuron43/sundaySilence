#include "MyGame.h"


// 初期化
void MyGame::Initialize() {
	////////////////////////////
	Framework::Initialize();

	postFXManager = std::make_unique<PostEffectManager>();
	postFXManager->Initialize(dxCommon);

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice());
	//パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	// FBX静的初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());




	// ゲームシーンの初期化
	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize(dxCommon, input);
}
// 終了
void MyGame::Finalize() {

	//delete gameScene;

	////////////////////////

	Framework::Finalize();
}

// 毎フレーム更新
void MyGame::Update() {

	Framework::Update();

	// ゲームシーンの毎フレーム処理
	gameScene->Update();

}

// 描画のフレームワークのポストエフェクトの扱いわからん
// 描画
void MyGame::Draw() {


	//// ポストエフェクト用ゲームシーンの描画
	postFXManager->TargetPreDraw(dxCommon->GetCommandList(), gameScene.get());

	//4.描画コマンドここから
	dxCommon->PreDraw();

	// ゲームシーンの描画
	//gameScene->Draw();

	//ポストエフェクトの描画
	postFXManager->Draw(dxCommon->GetCommandList());
	
	// Imgui受付終了
	imgui->End();
#ifdef _DEBUG
#endif
	// Imgui描画
	imgui->Draw();
	// 描画終了
	dxCommon->PostDraw();

	fps->FpsControlEnd();
	//4.描画コマンドここまで
}