#include "Framework.h"


void Framework::Run() {
	Initialize();
	while (true)
	{
		Update();
		if (IsEndRequest()) {
			break;
		}
		Draw();
	}

	Finalize();

}


void Framework::Initialize() {

	fps = new FPS();

	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化　
	input = new Input();
	input->Initialize(winApp);
	PadInput = new Pad_X_Input();

	//FPS変えたいとき
	fps->SetFrameRate(60);

	endRequest_ = false;
}

void Framework::Finalize() {

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
}

void Framework::Update() {

#pragma region ウィンドウメッセージ処理

	//アプリケーションが終わる時にmessageがWM_QUITになる
	if (winApp->ProcessMessage()) {
		Framework::endRequest_ = true;
	}

	fps->FpsControlBegin();

#pragma endregion

	//入力の更新
	input->Update();
	PadInput->Update();
	// Imgui受付開始
	imgui->Begin();

}