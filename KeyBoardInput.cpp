#include "KeyBoardInput.h"
#include "NewEngineWindow.h"
#include "InputManager.h"
#include <cassert>

void KeyBoardInput::Initialize()
{
	HRESULT result;

	// キーボードデバイスの生成
	result = Input::GetInstance().GetDirectInput()->
		CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	// 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void KeyBoardInput::Update()
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
bool KeyBoardInput::GetKey(BYTE key)
{
	return keys[key] == 128;
}

// キーを押した瞬間
bool KeyBoardInput::GetKeyTrigger(BYTE key)
{
	return keys[key] && !oldkeys[key];
}

// キーを離した瞬間
bool KeyBoardInput::GetKeyReleased(BYTE key)
{
	return !keys[key] && oldkeys[key];
}

KeyBoardInput& KeyBoardInput::GetInstance()
{
	static KeyBoardInput key;
	return key;
}
