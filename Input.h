#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include "KeyBourdInput.h"
#include "MouseInput.h"

class Input
{
private:
	IDirectInput8* directInput;

public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	static KeyBourdInput& Key();
	static MouseInput& Mouse();

	IDirectInput8* GetDirectInput();
	static Input& GetInstance();
private:
	Input() = default;
	~Input() = default;

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(const Input&&) = delete;
	Input& operator=(const Input&&) = delete;
};