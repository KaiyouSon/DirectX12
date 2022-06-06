#pragma once
#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "MouseInput.h"

class InputManager
{
public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

private:
	IDirectInput8* directInput;


	static KeyBoardInput& Key();
	static MouseInput& Mouse();

	IDirectInput8* GetDirectInput();
	static InputManager& GetInstance();
private:
	InputManager() = default;
	~InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(const InputManager&&) = delete;
	InputManager& operator=(const InputManager&&) = delete;
}typedef Input;