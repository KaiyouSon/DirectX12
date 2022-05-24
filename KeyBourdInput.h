#pragma once
#include <dinput.h>
class KeyBourdInput
{
private:
	IDirectInputDevice8* keyboard;
	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };
public:
	void Initialize();	// ������
	void Update();		// �X�V����

	// �L�[�̎擾�֘A
	bool GetKey(BYTE key);
	bool GetKeyTrigger(BYTE key);
	bool GetKeyReleased(BYTE key);

	static KeyBourdInput& GetInstance();
private:
	KeyBourdInput() = default;
	~KeyBourdInput() = default;

	KeyBourdInput(const KeyBourdInput&) = delete;
	KeyBourdInput& operator=(const KeyBourdInput&) = delete;
	KeyBourdInput(const KeyBourdInput&&) = delete;
	KeyBourdInput& operator=(const KeyBourdInput&&) = delete;
};