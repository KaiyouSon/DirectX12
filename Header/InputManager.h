#pragma once
#define DIRECTINPUT_VERSION 0x0800	// DirectInputのバージョン指定
#include "Header/JoypadInput.h"
#include "Header/KeyBoardInput.h"
#include "Header/MouseInput.h"
#include <dinput.h>
#include <wrl.h>

constexpr int BUTTON_A = 0;
constexpr int BUTTON_B = 1;
constexpr int BUTTON_X = 2;
constexpr int BUTTON_Y = 3;
constexpr int BUTTON_L1 = 4;
constexpr int BUTTON_R1 = 5;
constexpr int BUTTON_BACK = 6;
constexpr int BUTTON_START = 7;

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