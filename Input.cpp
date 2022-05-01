#include <cassert>
#include "Input.h"
#include "NewEngineWindow.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input input;
extern NewEngineWindow* newEngineWin;

void Input::Initialize()
{
	HRESULT result;

	// DirectInputの初期化
	result = DirectInput8Create(
		newEngineWin->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
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
		newEngineWin->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
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
