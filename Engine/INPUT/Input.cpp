#include "Input.h"
#include <cassert>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Input::Input() {

}
Input::~Input() {
	delete keybord_;
	delete Xpad_;
	delete mouse_;
}
void Input::Initialize(WinApp* winApp)
{
	keybord_ = new Keyboard_Input();
	keybord_->Initialize(winApp);
	
	Xpad_ = new Pad_X_Input();

	mouse_ = new MouseInput();
	mouse_->Initialize(winApp);
}

void Input::Update()
{
	keybord_->Update();
	Xpad_->Update();
	mouse_->Update();
}

bool Input::KeyboardPush(BYTE keyNumber)
{
	return keybord_->PushKey(keyNumber);
}

bool Input::KeyboardTrigger(BYTE keyNumber)
{
	return keybord_->TriggerKey(keyNumber);
}

bool Input::KeyboardRelease(BYTE keyNumber)
{
	return keybord_->ReleaseKey(keyNumber);
}


bool Input::Pad_X_ButtonTrigger(ControllerButton button) {
	return Xpad_->ButtonTrigger(button);
}

bool Input::Pad_X_StickTrigger(
	ControllerStick stickInput,
	const float& deadRange,
	const Vector2& deadRate) {
	return Xpad_->StickTrigger(stickInput, deadRange, deadRate);
}

bool Input::Pad_X_ButtonInput(ControllerButton button) {
	return Xpad_->ButtonInput(button);
}

bool Input::Pad_X_StickInput(
	ControllerStick stickInput,
	const float& deadRange,
	const Vector2& deadRate) {
	return Xpad_->StickInput(stickInput, deadRange, deadRate);
}

bool Input::Pad_X_ButtonOffTrigger(ControllerButton button) {
	return Xpad_->ButtonOffTrigger(button);
}

bool Input::Pad_X_StickOffTrigger(
	ControllerStick stickInput,
	const float& deadRang,
	const Vector2& deadRate) {
	return Xpad_->StickOffTrigger(stickInput, deadRang, deadRate);
}

Vector2 Input::Pad_X_GetLeftStickVec(const Vector2& deadRate) {
	return Xpad_->GetLeftStickVec(deadRate);
}

Vector2 Input::Pad_X_GetRightStickVec(const Vector2& deadRate) {
	return Xpad_->GetRightStickVec(deadRate);
}

void Input::Pad_X_ShakeController(
	const float& power,
	const int& span) {
	return Xpad_->ShakeController(power, span);
}


bool Input::MouseButtonPush(unsigned char mouseButtons) {
	return mouse_->PushMouseButton(mouseButtons);
}

bool Input::MouseButtonTrigger(unsigned char mouseButtons) {
	return mouse_->TriggerMouseButton(mouseButtons);
}

bool Input::MouseButtonRelease(unsigned char mouseButtons) {
	return mouse_->ReleaseMouseButton(mouseButtons);
}

Vector2 Input::GetMousePosition() {
	return mouse_->GetMousePosition();
}