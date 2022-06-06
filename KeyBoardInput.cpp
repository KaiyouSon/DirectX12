#include "KeyBoardInput.h"
#include "NewEngineWindow.h"
#include "InputManager.h"
#include <cassert>

void KeyBoardInput::Initialize()
{
	HRESULT result;

	// �L�[�{�[�h�f�o�C�X�̐���
	result = Input::GetInstance().GetDirectInput()->
		CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	// �W���`��
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void KeyBoardInput::Update()
{
	// �L�[�{�[�g���̎擾�J�n
	keyboard->Acquire();

	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾����
	keyboard->GetDeviceState(sizeof(keys), keys);
}

// �L�[��������Ă鎞
bool KeyBoardInput::GetKey(BYTE key)
{
	return keys[key] == 128;
}

// �L�[���������u��
bool KeyBoardInput::GetKeyTrigger(BYTE key)
{
	return keys[key] && !oldkeys[key];
}

// �L�[�𗣂����u��
bool KeyBoardInput::GetKeyReleased(BYTE key)
{
	return !keys[key] && oldkeys[key];
}

KeyBoardInput& KeyBoardInput::GetInstance()
{
	static KeyBoardInput key;
	return key;
}
