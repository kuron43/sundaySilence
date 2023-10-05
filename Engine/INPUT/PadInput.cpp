#include "PadInput.h"


Pad_X_Input::Pad_X_Input() {

}
Pad_X_Input::~Pad_X_Input() {

}

bool Pad_X_Input::StickInDeadZone(Vector2& Thumb, const Vector2& DeadRate)
{
	bool x = false;
	bool y = false;

	if ((Thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x
		&& Thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x))
	{
		Thumb.x = 0.0f;
		x = true;
	}
	if ((Thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y
		&& Thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y))
	{
		Thumb.y = 0.0f;
		y = true;
	}

	if (x && y)
	{
		return true;
	}

	return false;
}

void Pad_X_Input::Update()
{
	oldXinputState = xinputState;
	ZeroMemory(&xinputState, sizeof(XINPUT_STATE));

	//コントローラー取得
	DWORD dwResult = XInputGetState(0, &xinputState);

	if (dwResult == ERROR_SUCCESS)
	{
		//コントローラーが接続されている
		if (0 < shakeTimer)
		{
			shakeTimer--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer == 0)
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
			}
			else
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
			}

			XInputSetState(dwResult, &vibration);
		}
	}
	else
	{
		//コントローラーが接続されていない
	}
}

bool Pad_X_Input::ButtonTrigger(ControllerButton button)
{
	//トリガー
	if (button == LT)
	{
		return oldXinputState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else if (button == RT)
	{
		return oldXinputState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else
	{
		return !(oldXinputState.Gamepad.wButtons & button) && ButtonInput(button);
	}
}

bool Pad_X_Input::StickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 oldVec;
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;
	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = !(deadRange < (oldVec.y / STICK_INPUT_MAX)) && deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = !(oldVec.y / STICK_INPUT_MAX < -deadRange) && vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = !(deadRange < (oldVec.x / STICK_INPUT_MAX)) && deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = !(oldVec.x / STICK_INPUT_MAX < -deadRange) && vec.x / STICK_INPUT_MAX < -deadRange;
	}
	else
	{
		assert(0);
	}

	return result;
}

bool Pad_X_Input::ButtonInput(ControllerButton button)
{
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bLeftTrigger;
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bRightTrigger;
	}
	else
	{
		return xinputState.Gamepad.wButtons & button;
	}
}

bool Pad_X_Input::StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, deadRate))return false;

	if (stickInput % 4 == L_UP)
	{
		return deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		return  vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		return deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		return  vec.x / STICK_INPUT_MAX < -deadRange;
	}

	assert(0);
	return false;
}

bool Pad_X_Input::ButtonOffTrigger(ControllerButton button)
{
	//トリガー
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bLeftTrigger && !ButtonInput(button);
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bRightTrigger && !ButtonInput(button);
	}
	//ボタン
	else
	{
		return (oldXinputState.Gamepad.wButtons & button) && !ButtonInput(button);
	}
}

bool Pad_X_Input::StickOffTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	 Vector2 oldVec;
	 Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = deadRange < (oldVec.y / STICK_INPUT_MAX) && !(deadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = oldVec.y / STICK_INPUT_MAX < -deadRange && !(vec.y / STICK_INPUT_MAX < -deadRange);
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = deadRange < (oldVec.x / STICK_INPUT_MAX) && !(deadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = oldVec.x / STICK_INPUT_MAX < -deadRange && !(vec.x / STICK_INPUT_MAX < -deadRange);
	}
	else
	{
		assert(0);
	}

	return result;
}

 Vector2 Pad_X_Input::GetLeftStickVec(const Vector2& deadRate)
{

	Vector2 result(static_cast<float>(xinputState.Gamepad.sThumbLX), static_cast<float>(-xinputState.Gamepad.sThumbLY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

 Vector2 Pad_X_Input::GetRightStickVec(const Vector2& deadRate)
{
	Vector2 result(static_cast<float>(xinputState.Gamepad.sThumbRX), static_cast<float>(-xinputState.Gamepad.sThumbRY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;;
}

void Pad_X_Input::ShakeController(const float& power, const uint32_t& span)
{
	if (!(0 < power && power <= 1.0f))
	{
		assert(0);
	}

	shakePower = power;
	shakeTimer = span;
}

