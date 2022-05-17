#include <cassert>
#include "Input.h"
#include "NewEngineWindow.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize()
{
	HRESULT result;

	// DirectInputの初期化
	result = DirectInput8Create(
		NewEngineWindow::GetInstance().GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	// 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

	// マウスデバイスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, nullptr);
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

void Input::Update()
{
	// キーボート情報の取得開始
	keyboard->Acquire();

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	// 最新のキーボード情報を取得する
	keyboard->GetDeviceState(sizeof(keys), keys);

	// マウス情報の取得開始
	mouse->Acquire();

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	oldMouseInput = mouseInput;

	// 最新のキーボード情報を取得する
	mouse->GetDeviceState(sizeof(mouseInput), &mouseInput);


	POINT tmpMousePos;
	GetCursorPos(&tmpMousePos);

	// ウィンドウ座標に変換する
	ScreenToClient(NewEngineWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
}

// キーが押されてる時
bool Input::GetKey(BYTE key)
{
	return keys[key] == 128;
}

// キーを押した瞬間
bool Input::GetKeyTrigger(BYTE key)
{
	return keys[key] && !oldkeys[key];
}

// キーを離した瞬間
bool Input::GetKeyReleased(BYTE key)
{
	return !keys[key] && oldkeys[key];
}

bool Input::GetMouseLeft()
{
	return mouseInput.rgbButtons[0] & (0x80);
}

bool Input::GetMouseLeftTrigger()
{
	return (mouseInput.rgbButtons[0] & (0x80)) &&
		!(oldMouseInput.rgbButtons[0] & (0x80));
}
bool Input::GetMouseLeftReleased()
{
	return !(mouseInput.rgbButtons[0] & (0x80)) &&
		(oldMouseInput.rgbButtons[0] & (0x80));
}

bool Input::GetMouseRight()
{
	return mouseInput.rgbButtons[1] & (0x80);
}

bool Input::GetMouseRightTrigger()
{
	return (mouseInput.rgbButtons[1] & (0x80)) &&
		!(oldMouseInput.rgbButtons[1] & (0x80));
}

bool Input::GetMouseRightReleased()
{
	return !(mouseInput.rgbButtons[1] & (0x80)) &&
		(oldMouseInput.rgbButtons[1] & (0x80));
}

bool Input::GetMouseWheel()
{
	return mouseInput.rgbButtons[2] & (0x80);
}

bool Input::GetMouseWheelTrigger()
{
	return (mouseInput.rgbButtons[2] & (0x80)) &&
		!(oldMouseInput.rgbButtons[2] & (0x80));
}

bool Input::GetMouseWheelReleased()
{
	return !(mouseInput.rgbButtons[2] & (0x80)) &&
		(oldMouseInput.rgbButtons[2] & (0x80));
}

Vec2 Input::GetMousePos()
{
	return mousePos;
}

Vec3 Input::GetMouseVelocity()
{
	Vec3 tmp = { (float)mouseInput.lX,(float)mouseInput.lY,(float)mouseInput.lZ };
	return tmp;
}


Input& Input::GetInstance()
{
	static Input input;
	return input;
}