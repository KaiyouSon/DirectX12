#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include <dinput.h>

class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };

	HWND hwnd;

public:
	void Initialize();
	void Update();
	bool GetKey(BYTE key);

};

extern Input input;