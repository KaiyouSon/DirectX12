#pragma once

#define DIRECTINPUT_VERSION 0x0800	// DirectInput�̃o�[�W�����w��
#include <dinput.h>

class Input
{
private:
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };

public:
	void Initialize();	// ������
	void Update();		// �X�V����

	/// <summary>
	/// �L�[��������Ă鎞
	/// </summary>
	/// <param name="keys">�L�[�ԍ�( DIK_0 ��)</param>
	/// <returns>�L�[��������Ă鎞</returns>
	bool GetKey(BYTE key);

	/// <summary>
	/// �L�[���������u��
	/// </summary>
	/// <param name="keys">�L�[�ԍ�( DIK_0 ��)</param>
	/// <returns>�L�[���������u��</returns>
	bool GetKeyTrigger(BYTE key);

	/// <summary>
	/// �L�[�𗣂����u��
	/// </summary>
	/// <param name="keys">�L�[�ԍ�( DIK_0 ��)</param>
	/// <returns>�L�[�𗣂����u��</returns>
	bool GetKeyReleased(BYTE key);

	static Input& GetInstance();

private:
	Input() = default;
	~Input() = default;

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(const Input&&) = delete;
	Input& operator=(const Input&&) = delete;

};