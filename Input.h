#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInput�̃o�[�W�����w��
#include "KeyBourdInput.h"
#include "MouseInput.h"

class Input
{
private:
	IDirectInput8* directInput;

public:
	void Initialize();	// ������
	void Update();		// �X�V����

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