#pragma once
#include <windows.h>
#include <wrl.h>
#include <dinput.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定

class Keyboard_Input
{
public:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数

	Keyboard_Input();
	~Keyboard_Input();
	// 初期化
	void Initialize(WinApp* winApp);

	// 更新
	void Update();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name = "keyNumber">キー番号(DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// </param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <reutrns>トリガーか</params>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// </param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <reutrns>離されたか</params>
	bool ReleaseKey(BYTE keyNumber);

private: // メンバ変数
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	// DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	// 全キーの状態
	BYTE key[256] = {};
	// 前回の全キーの状態
	BYTE keyPre[256] = {};
	//windwsAPI
	WinApp* winApp_ = nullptr;


};

