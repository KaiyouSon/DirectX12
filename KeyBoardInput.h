#pragma once
#include <dinput.h>
#include <wrl.h>
class KeyBoardInput
{
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	BYTE keys[256] = { 0 };
	BYTE oldkeys[256] = { 0 };
public:
	void Initialize();	// ������
	void Update();		// �X�V����

	// �L�[�̎擾�֘A
	bool GetKey(BYTE key);
	bool GetKeyTrigger(BYTE key);
	bool GetKeyReleased(BYTE key);

	static KeyBoardInput& GetInstance();
private:
	KeyBoardInput() = default;
	~KeyBoardInput() = default;

	KeyBoardInput(const KeyBoardInput&) = delete;
	KeyBoardInput& operator=(const KeyBoardInput&) = delete;
	KeyBoardInput(const KeyBoardInput&&) = delete;
	KeyBoardInput& operator=(const KeyBoardInput&&) = delete;
};