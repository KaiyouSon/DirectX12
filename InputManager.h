#pragma once
#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "MouseInput.h"

class InputManager
{
private:
	Microsoft::WRL::ComPtr<IDirectInput8> directInput;

public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	static JoypadInput& PadInstance();
	static KeyBoardInput& KeyInstance();
	static MouseInput& MouseInstance();

	Microsoft::WRL::ComPtr<IDirectInput8> GetDirectInput();

	static InputManager& GetInstance();
private:
	InputManager() = default;
	~InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(const InputManager&&) = delete;
	InputManager& operator=(const InputManager&&) = delete;
}typedef Input;