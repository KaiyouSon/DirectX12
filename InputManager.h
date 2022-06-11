#pragma once
#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include <dinput.h>
#include <wrl.h>
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "MouseInput.h"

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_L1 4
#define BUTTON_R1 5
#define BUTTON_BACK 6
#define BUTTON_START 7

class InputManager
{
private:
	Microsoft::WRL::ComPtr<IDirectInput8> directInput;

public:
	void Initialize();	// 初期化
	void Update();		// 更新処理

	Microsoft::WRL::ComPtr<IDirectInput8> GetDirectInput();

	static InputManager* GetInstance();
	static void DestoryInstance();
private:
	InputManager() = default;
	~InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(const InputManager&&) = delete;
	InputManager& operator=(const InputManager&&) = delete;
}typedef Input;

extern JoypadInput* pad;
extern KeyBoardInput* key;
extern MouseInput* mouse;