#include <cassert>
#include "Input.h"
#include "NewEngineWindow.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input input;
extern NewEngineWindow* newEngineWin;

void Input::Initialize()
{
	HRESULT result;

	// DirectInput�̏�����
	result = DirectInput8Create(
		newEngineWin->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	// �W���`��
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		newEngineWin->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
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
bool Input::GetKey(BYTE key)
{
	return keys[key] == 128;
}

// �L�[���������u��
bool Input::GetKeyTrigger(BYTE key)
{
	return keys[key] && !oldkeys[key];
}

// �L�[�𗣂����u��
bool Input::GetKeyReleased(BYTE key)
{
	return !keys[key] && oldkeys[key];
}
