#pragma once
#pragma warning(push)
#pragma warning(disable: 4820)

#include <wrl.h>
#include <Windows.h>
#include <dinput.h>
#include <WinUser.h>
#pragma warning(pop)


#include "WinApp.h"
#include "Vector2.h"

enum mouseInput {
	LEFT_MOUSE = 0,
	RIGHT_MOUSE = 1,
};


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

