#pragma once
#include <wrl.h>
#include <Windows.h>
#include <dinput.h>
#include <WinUser.h>
#include "WinApp.h"
#include "Vector2.h"

class MouseInput
{
private:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// マウス入力初期化
	ComPtr<IDirectInputDevice8> mouse = nullptr;
	// DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;

	DIMOUSESTATE mouseButton;
	DIMOUSESTATE oldMouseButton;
	WinApp* winApp_;
	Vector2 mousePos_;

private:
	void UpdatePointPos();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// マウス操作
	/// </summary>
	/// <param name="mouseButtons"></param>
	/// <returns></returns>
	bool PushMouseButton(unsigned char mouseButtons);
	bool TriggerMouseButton(unsigned char mouseButtons);
	bool ReleaseMouseButton(unsigned char mouseButtons);
	Vector2 GetMousePosition();
};

