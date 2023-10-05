#pragma once
#include "WinApp.h"
#include <stdint.h>

#include "Keyboard_Input.h"
#include "PadInput.h"
#include "MouseInput.h"



// 入力
class Input
{
public:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private: // メンバ変数
	
	Keyboard_Input* keybord_;
	Pad_X_Input* Xpad_;
	MouseInput* mouse_;
	

public: // メンバ関数
	Input();
	~Input();

	// 初期化
	void Initialize(WinApp* winApp);

	// 更新
	void Update();
#pragma region キーボード用関数

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name = "keyNumber">キー番号(DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool KeyboardPush(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// </param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <reutrns>トリガーか</params>
	bool KeyboardTrigger(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	/// </param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <reutrns>離されたか</params>
	bool KeyboardRelease(BYTE keyNumber);

#pragma endregion キーボード用関数

#pragma region Xbox Pad用関数

	/// <summary>
	/// コントローラーボタンのトリガー入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したか</returns>
	bool Pad_X_ButtonTrigger(ControllerButton button);

	/// <summary>
	/// コントローラースティックのトリガー入力
	/// </summary>
	/// <param name="stickInput">コントローラースティック方向</param>
	/// <param name="deadRange">デッドゾーンの範囲</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns>倒したかどうか</returns>
	bool Pad_X_StickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate);

	/// <summary>
	/// コントローラーボタンの入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したか</returns>
	bool Pad_X_ButtonInput(ControllerButton button);

	/// <summary>
	/// コントローラースティックの入力
	/// </summary>
	/// <param name="stickInput">コントローラースティック方向</param>
	/// <param name="deadRange">デッドゾーンの範囲</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns>倒したかどうか</returns>
	bool Pad_X_StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate);

	/// <summary>
	/// コントローラーボタンの離した瞬間
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>離したか</returns>
	bool Pad_X_ButtonOffTrigger(ControllerButton button);

	/// <summary>
	/// コントローラースティックの離した瞬間
	/// </summary>
	/// <param name="stickInput">コントローラースティック方向</param>
	/// <param name="deadRange">デッドゾーンの範囲初期値0.3f</param>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns>離したか</returns>
	bool Pad_X_StickOffTrigger(ControllerStick stickInput, const float& deadRang, const Vector2& deadRate);


	/// <summary>
	/// コントローラーの左スティックのベクトル
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns>ベクトル</returns>
	Vector2 Pad_X_GetLeftStickVec(const Vector2& deadRate);

	/// <summary>
	/// コントローラーの右スティックのベクトル
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い初期値1.0f</param>
	/// <returns>ベクトル</returns>
	Vector2 Pad_X_GetRightStickVec(const Vector2& deadRate);

	/// <summary>
	/// コントローラーを振動させる
	/// </summary>
	/// <param name="power">振動の強さ0.0f～1.0f</param>
	/// <param name="span">振動の時間フレーム</param>
	void Pad_X_ShakeController(const float& power, const uint32_t& span);

#pragma endregion Xbox Pad用関数
#pragma region マウス用関数

	/// <summary>
	/// マウスボタンの入力
	/// </summary>
	/// <param name="mouseButtons"></param>
	bool MouseButtonPush(unsigned char mouseButtons);
	/// <summary>
	/// マウスボタンの押した瞬間
	/// </summary>
	/// <param name="mouseButtons"></param>
	/// <returns></returns>
	bool MouseButtonTrigger(unsigned char mouseButtons);
	/// <summary>
	/// マウスボタンの離した瞬間
	/// </summary>
	/// <param name="mouseButtons"></param>
	/// <returns></returns>
	bool MouseButtonRelease(unsigned char mouseButtons);
	/// <summary>
	/// マウスの座標取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetMousePosition();

#pragma endregion マウス用関数
};