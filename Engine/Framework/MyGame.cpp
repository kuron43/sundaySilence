#include "MyGame.h"


// 初期化
void MyGame::Initialize() {

	fps = new FPS;
	fbxManager = FbxManager::Create();

	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化　
	input = new Input();
	input->Initialize(winApp);
	PadInput = new Pad_X_Input();

	postEffect = new PostEffect();
	postEffect->Initialize(dxCommon);
	postEffect->SetKernelSize(10);
	postEffect->SetRadialBlur(Vector2(winApp->window_width / 2, winApp->window_height / 2), 0.1, 1);
	postEffect->SetShadeNumber(2);

	// ImGuiの初期化
	imgui = new ImGuiManager();
	imgui->Initialize(winApp, dxCommon);

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	// FBX静的初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());

	//FPS変えたいとき
	fps->SetFrameRate(60);

	endRequest_ = false;

	////////////////////////////
	Framework::Initialize();

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);


}
// 終了
void MyGame::Finalize() {

	delete gameScene;

	postEffect->Finalize();
	delete postEffect;

	////////////////////////

	Framework::Finalize();
}
// 毎フレーム更新
void MyGame::Update() {

	Framework::Update();

	// ゲームシーンの毎フレーム処理
	gameScene->Update();

	if (input->KeyboardTrigger(DIK_0)) {
		postEffect->SetShadeNumber(0);
	}
	if (input->KeyboardTrigger(DIK_1)) {
		postEffect->SetShadeNumber(3);
	}

}
// 描画のフレームワークのポストエフェクトの扱いわからん
// 描画
void MyGame::Draw() {


	// ゲームシーンの描画
	postEffect->PreDrawScene(dxCommon->GetCommandList());
	gameScene->Draw();
	postEffect->PostDrawScene();

	///////////////////////////////////////
	//4.描画コマンドここから
	dxCommon->PreDraw();

	// デモウィンドウの表示オン
	//ImGui::ShowDemoWindow();

	//ポストエフェクトの描画
	postEffect->Draw(dxCommon->GetCommandList());

	// Imgui受付終了
	imgui->End();
	// Imgui描画
	imgui->Draw();

	// 描画終了
	dxCommon->PostDraw();

	fps->FpsControlEnd();
	//4.描画コマンドここまで
}