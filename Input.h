#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include <dinput.h>
#include "MathUtil.h"

class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
	IDirectInputDevice8* mouse = nullptr;

	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };

	DIMOUSESTATE2 mouseInput;
	DIMOUSESTATE2 oldMouseInput;

	Vec2 mousePos;

public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	// キーの取得関連
	bool GetKey(BYTE key);
	bool GetKeyTrigger(BYTE key);
	bool GetKeyReleased(BYTE key);

	// マウスの取得関連
	bool GetMouseLeft();
	bool GetMouseLeftTrigger();
	bool GetMouseLeftReleased();
	bool GetMouseRight();
	bool GetMouseRightTrigger();
	bool GetMouseRightReleased();
	bool GetMouseWheel();
	bool GetMouseWheelTrigger();
	bool GetMouseWheelReleased();
	Vec2 GetMousePos();
	Vec3 GetMouseVelocity();

	static Input& GetInstance();

private:
	Input() = default;
	~Input() = default;

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(const Input&&) = delete;
	Input& operator=(const Input&&) = delete;

};