#include "Input.h"
#include <cassert>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//using namespace Microsoft::WRL;

void Input::Initialize(WinApp* winApp)
{
	this->winApp_ = winApp;

	HRESULT result;

	// DirectInputのインスタンス生成
	/*ComPtr<IDirectInput8> directInput = nullptr;*/
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	//ComPtr<IDirectInputDevice8> keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	HRESULT result;

	// 前回のキー入力を保持
	memcpy(keyPre, key, sizeof(key));

	// キーボード情報の取得開始
	result = keyboard->Acquire();

	// 全キーの入力状態を取得する
	/*BYTE key[256] = {};*/
	result = keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	// 指定キーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	// そうではなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber])
	{
		if (keyPre[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}

/// <summary>
/// キーのトリガーをチェック
/// </summary>
/// </param name="keyNumber">キー番号( DIK_0 等)</param>
/// <reutrns>離されたか</params>
bool Input::ReleaseKey(BYTE keyNumber) {
	if (keyPre[keyNumber])
	{
		if (key[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}