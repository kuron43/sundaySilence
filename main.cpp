
#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "ImGuiManager.h"
#include <imgui.h>


#include "GameScene.h"
#include "PadInput.h"
#include "PostEffect.h"

#include "fbxsdk.h"



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	FbxManager* fbxManager = FbxManager::Create();
#pragma region WindowsAPI初期化処理


	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	Pad_X_Input* PadInput = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;

	ImGuiManager* imgui = nullptr;

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
	postEffect->SetShadeNumber(1);

	// ImGuiの初期化
	imgui = new ImGuiManager();
	imgui->Initialize(winApp,dxCommon);

#pragma endregion

#pragma region DirectX初期化処理
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice(),dxCommon->GetCommandList());
	// FBX静的初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());

#pragma endregion

#pragma region 描画初期化処理

	////////////////////////////
	//------音声読み込み--------//
	///////////////////////////

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);
	

	//FPS変えたいとき
	fps->SetFrameRate(60);

#pragma endregion
	//ゲームループ
	while (true) {
#pragma region ウィンドウメッセージ処理

		//アプリケーションが終わる時にmessageがWM_QUITになる
		if (winApp->ProcessMessage()) {
			break;
		}
		/*if (input->KeyboardPush(DIK_ESCAPE)) {
			break;
		}*/


		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX毎フレーム処理
		/////////////////////////////////////////////////////
		//----------DireceX毎フレーム処理　ここから------------//
		///////////////////////////////////////////////////

		//入力の更新
		input->Update();
		PadInput->Update();
		// Imgui受付開始
		imgui->Begin();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();		

		//////////////////////////////////////////////
		//-------DireceX毎フレーム処理　ここまで--------//
		////////////////////////////////////////////

#pragma endregion

#pragma region グラフィックスコマンド

		// ゲームシーンの描画
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect->PostDrawScene();

		//4.描画コマンドここから
		dxCommon->PreDraw();
		
		// デモウィンドウの表示オン
		ImGui::ShowDemoWindow();


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

#pragma endregion

#pragma region 画面入れ替え

#pragma endregion
	}
#pragma region  WindowsAPI後始末

	/*ID3D12DebugDevice* debugInterface;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(&debugInterface))) {
		debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
		debugInterface->Release();
	}*/

	delete gameScene;

	postEffect->Finalize();
	delete postEffect;

	imgui->Finalize();
	//WindowsAPIの終了処理
	winApp->Finalize();
	delete imgui;

	//入力開放
	delete input;
	delete PadInput;
	//WindowsAPI開放
	delete winApp;
	delete dxCommon;

	delete fps;
	
#pragma endregion
	return 0;
}