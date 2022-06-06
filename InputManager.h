#pragma once
#define DIRECTINPUT_VERSION 0x0800	// DirectInput�̃o�[�W�����w��
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "MouseInput.h"

class InputManager
{
public:
	void Initialize();	// ������
	void Update();		// �X�V����

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