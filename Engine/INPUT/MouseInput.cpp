#include "MouseInput.h"
#include "Input.h"
#include<cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/// <summary>
	/// 初期化
	/// </summary>
void MouseInput::Initialize(WinApp* winApp) {
	HRESULT result;
	winApp_ = winApp;

	// DirectInputの初期化
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//マウスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));

	result = mouse->SetDataFormat(&c_dfDIMouse);

	result = mouse->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));
}

/// <summary>
/// 更新
/// </summary>
void MouseInput::Update() {
	//HRESULT result;

	mouse->Acquire();

	//全キーの入力状態を取得する
	for (uint32_t i = 0; i < sizeof(DIMOUSESTATE::rgbButtons); i++) {
		oldMouseButton.rgbButtons[i] = mouseButton.rgbButtons[i];
	}

	mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseButton);
	UpdatePointPos();
}
void MouseInput::UpdatePointPos() {
	Vector2 windowWH = Vector2(WinApp::window_width / 2, WinApp::window_height / 2);
	POINT mousePosition;
	//マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = winApp_->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	float xPos_absolute, yPos_absolute;

	float xPos = windowWH.x;  //移動させたいｘ座標（ウィンドウ内の相対座標）
	float yPos = windowWH.y; //移動させたいｙ座標（ウィンドウ内の相対座標）

	WINDOWINFO windowInfo;
	//ウィンドウの位置を取得
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &windowInfo);

	//マウスの移動先の絶対座標（モニター左上からの座標）
	xPos_absolute = xPos + windowInfo.rcWindow.left + 8;//なんかずれてるから直す
	yPos_absolute = yPos + windowInfo.rcWindow.top + 31; //ウィンドウのタイトルバーの分（31px）をプラス

	//SetCursorPos(xPos_absolute, yPos_absolute);//移動させる

	//mousePos_ = { xPos_absolute,yPos_absolute };

	Vector2 mousePos;
	mousePos.x = static_cast<float>(mousePosition.x);
	mousePos.y = static_cast<float>(mousePosition.y);

	//マウスの移動量を取得
	mousePos_ = Vector2(0, 0);
	mousePos_ = (Vector2(mousePos.x, -mousePos.y) - Vector2(windowWH.x, -windowWH.y));//座標軸で回転している関係でこうなる(XとYが入れ替え)

}

bool MouseInput::PushMouseButton(unsigned char mouseButtons) {
	return mouseButton.rgbButtons[mouseButtons];
}

bool MouseInput::TriggerMouseButton(unsigned char mouseButtons) {
	return mouseButton.rgbButtons[mouseButtons] && !oldMouseButton.rgbButtons[mouseButtons];
}

bool MouseInput::ReleaseMouseButton(unsigned char mouseButtons) {
	return !mouseButton.rgbButtons[mouseButtons] && oldMouseButton.rgbButtons[mouseButtons];;
}

Vector2 MouseInput::GetMousePosition() {
	return mousePos_;
}