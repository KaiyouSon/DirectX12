#include <cassert>
#include "Input.h"
#include "NewEngineWindow.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize()
{
	HRESULT result;

	// DirectInput�̏�����
	result = DirectInput8Create(
		NewEngineWindow::GetInstance().GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
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
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

	// �}�E�X�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, nullptr);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = mouse->SetDataFormat(&c_dfDIMouse2); // �g��8�{�^���܂�
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = mouse->SetCooperativeLevel(
		NewEngineWindow::GetInstance().GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
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

	// �}�E�X���̎擾�J�n
	mouse->Acquire();

	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	oldMouseInput = mouseInput;

	// �ŐV�̃L�[�{�[�h�����擾����
	mouse->GetDeviceState(sizeof(mouseInput), &mouseInput);


	POINT tmpMousePos;
	GetCursorPos(&tmpMousePos);

	// �E�B���h�E���W�ɕϊ�����
	ScreenToClient(NewEngineWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
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

bool Input::GetMouseLeft()
{
	return mouseInput.rgbButtons[0] & (0x80);
}

bool Input::GetMouseLeftTrigger()
{
	return (mouseInput.rgbButtons[0] & (0x80)) &&
		!(oldMouseInput.rgbButtons[0] & (0x80));
}
bool Input::GetMouseLeftReleased()
{
	return !(mouseInput.rgbButtons[0] & (0x80)) &&
		(oldMouseInput.rgbButtons[0] & (0x80));
}

bool Input::GetMouseRight()
{
	return mouseInput.rgbButtons[1] & (0x80);
}

bool Input::GetMouseRightTrigger()
{
	return (mouseInput.rgbButtons[1] & (0x80)) &&
		!(oldMouseInput.rgbButtons[1] & (0x80));
}

bool Input::GetMouseRightReleased()
{
	return !(mouseInput.rgbButtons[1] & (0x80)) &&
		(oldMouseInput.rgbButtons[1] & (0x80));
}

bool Input::GetMouseWheel()
{
	return mouseInput.rgbButtons[2] & (0x80);
}

bool Input::GetMouseWheelTrigger()
{
	return (mouseInput.rgbButtons[2] & (0x80)) &&
		!(oldMouseInput.rgbButtons[2] & (0x80));
}

bool Input::GetMouseWheelReleased()
{
	return !(mouseInput.rgbButtons[2] & (0x80)) &&
		(oldMouseInput.rgbButtons[2] & (0x80));
}

Vec2 Input::GetMousePos()
{
	return mousePos;
}

Vec3 Input::GetMouseVelocity()
{
	Vec3 tmp = { (float)mouseInput.lX,(float)mouseInput.lY,(float)mouseInput.lZ };
	return tmp;
}


Input& Input::GetInstance()
{
	static Input input;
	return input;
}