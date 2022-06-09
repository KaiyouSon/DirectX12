#include "MouseInput.h"
#include "NewEngineWindow.h"
#include "InputManager.h"
#include <cassert>

void MouseInput::Initialize()
{
	HRESULT result;

	// マウスデバイスの生成
	result = Input::GetInstance().GetDirectInput()->
		CreateDevice(GUID_SysMouse, &mouse, nullptr);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = mouse->SetDataFormat(&c_dfDIMouse2); // 拡張8ボタンまで
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = mouse->SetCooperativeLevel(
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));
}

void MouseInput::Update()
{
	// マウス情報の取得開始
	mouse->Acquire();

	// 最新のマウス情報だったものは1フレーム前のキーボード情報として保存
	oldMouseInput = mouseInput;

	// 最新のマウス情報を取得する
	mouse->GetDeviceState(sizeof(mouseInput), &mouseInput);

	POINT tmpMousePos;
	GetCursorPos(&tmpMousePos);

	// ウィンドウ座標に変換する
	ScreenToClient(NewEngineWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
}

bool MouseInput::GetMouseLeft()
{
	return mouseInput.rgbButtons[0] & (0x80);
}

bool MouseInput::GetMouseLeftTrigger()
{
	return (mouseInput.rgbButtons[0] & (0x80)) &&
		!(oldMouseInput.rgbButtons[0] & (0x80));
}
bool MouseInput::GetMouseLeftReleased()
{
	return !(mouseInput.rgbButtons[0] & (0x80)) &&
		(oldMouseInput.rgbButtons[0] & (0x80));
}

bool MouseInput::GetMouseRight()
{
	return mouseInput.rgbButtons[1] & (0x80);
}

bool MouseInput::GetMouseRightTrigger()
{
	return (mouseInput.rgbButtons[1] & (0x80)) &&
		!(oldMouseInput.rgbButtons[1] & (0x80));
}

bool MouseInput::GetMouseRightReleased()
{
	return !(mouseInput.rgbButtons[1] & (0x80)) &&
		(oldMouseInput.rgbButtons[1] & (0x80));
}

bool MouseInput::GetMouseWheel()
{
	return mouseInput.rgbButtons[2] & (0x80);
}

bool MouseInput::GetMouseWheelTrigger()
{
	return (mouseInput.rgbButtons[2] & (0x80)) &&
		!(oldMouseInput.rgbButtons[2] & (0x80));
}

bool MouseInput::GetMouseWheelReleased()
{
	return !(mouseInput.rgbButtons[2] & (0x80)) &&
		(oldMouseInput.rgbButtons[2] & (0x80));
}

Vec2 MouseInput::GetMousePos()
{
	return mousePos;
}

Vec3 MouseInput::GetMouseVelocity()
{
	Vec3 tmp = { (float)mouseInput.lX,(float)mouseInput.lY,(float)mouseInput.lZ };
	return tmp;
}

MouseInput& MouseInput::GetInstance()
{
	static MouseInput mouse;
	return mouse;
}