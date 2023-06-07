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