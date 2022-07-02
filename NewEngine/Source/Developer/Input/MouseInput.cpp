#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Input/MouseInput.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include <cassert>

void MouseInput::Initialize()
{
	HRESULT result;

	// マウスデバイスの生成
	result = Input::GetInstance()->GetDirectInput()->
		CreateDevice(GUID_SysMouse, &mouse, nullptr);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = mouse->SetDataFormat(&c_dfDIMouse2); // 拡張8ボタンまで
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = mouse->SetCooperativeLevel(
		RenderWindow::GetInstance().GetHwnd(),
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
	ScreenToClient(RenderWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
}

bool MouseInput::GetClick(const int& mouse)
{
	return mouseInput.rgbButtons[mouse] & (0x80);
}

bool MouseInput::GetClickTrigger(const int& mouse)
{
	return (mouseInput.rgbButtons[mouse] & (0x80)) &&
		!(oldMouseInput.rgbButtons[mouse] & (0x80));
}

bool MouseInput::GetClickReleased(const int& mouse)
{
	return !(mouseInput.rgbButtons[mouse] & (0x80)) &&
		(oldMouseInput.rgbButtons[mouse] & (0x80));
}

Vec2 MouseInput::GetMousePos()
{
	return mousePos;
}

float MouseInput::GetWheelVec()
{
	Vec3 vec = { (float)mouseInput.lX ,(float)mouseInput.lY ,(float)mouseInput.lZ };
	return vec.z;
}

MouseInput* MouseInput::GetInstance()
{
	static MouseInput* mouse = new MouseInput;
	return mouse;
}

void MouseInput::DestoryInstance()
{
	delete GetInstance();
}
