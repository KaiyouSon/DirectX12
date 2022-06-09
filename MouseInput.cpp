#include "MouseInput.h"
#include "NewEngineWindow.h"
#include "InputManager.h"
#include <cassert>

void MouseInput::Initialize()
{
	HRESULT result;

	// �}�E�X�f�o�C�X�̐���
	result = Input::GetInstance().GetDirectInput()->
		CreateDevice(GUID_SysMouse, &mouse, nullptr);
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

void MouseInput::Update()
{
	// �}�E�X���̎擾�J�n
	mouse->Acquire();

	// �ŐV�̃}�E�X��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	oldMouseInput = mouseInput;

	// �ŐV�̃}�E�X�����擾����
	mouse->GetDeviceState(sizeof(mouseInput), &mouseInput);

	POINT tmpMousePos;
	GetCursorPos(&tmpMousePos);

	// �E�B���h�E���W�ɕϊ�����
	ScreenToClient(NewEngineWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
}

bool MouseInput::GetMouseLeft()
{
	return mouseInput.rgbButtons[0] & (0x80);
}

bool MouseInput::GetMouseLeftTrigger()
{
	return (mouseInput.rgbButtons[0] & (0x80)) &&
		!(oldMouseInput.rgbButtons[0] & (0x80));
}
bool MouseInput::GetMouseLeftReleased()
{
	return !(mouseInput.rgbButtons[0] & (0x80)) &&
		(oldMouseInput.rgbButtons[0] & (0x80));
}

bool MouseInput::GetMouseRight()
{
	return mouseInput.rgbButtons[1] & (0x80);
}

bool MouseInput::GetMouseRightTrigger()
{
	return (mouseInput.rgbButtons[1] & (0x80)) &&
		!(oldMouseInput.rgbButtons[1] & (0x80));
}

bool MouseInput::GetMouseRightReleased()
{
	return !(mouseInput.rgbButtons[1] & (0x80)) &&
		(oldMouseInput.rgbButtons[1] & (0x80));
}

bool MouseInput::GetMouseWheel()
{
	return mouseInput.rgbButtons[2] & (0x80);
}

bool MouseInput::GetMouseWheelTrigger()
{
	return (mouseInput.rgbButtons[2] & (0x80)) &&
		!(oldMouseInput.rgbButtons[2] & (0x80));
}

bool MouseInput::GetMouseWheelReleased()
{
	return !(mouseInput.rgbButtons[2] & (0x80)) &&
		(oldMouseInput.rgbButtons[2] & (0x80));
}

Vec2 MouseInput::GetMousePos()
{
	return mousePos;
}

Vec3 MouseInput::GetMouseVelocity()
{
	Vec3 tmp = { (float)mouseInput.lX,(float)mouseInput.lY,(float)mouseInput.lZ };
	return tmp;
}

MouseInput& MouseInput::GetInstance()
{
	static MouseInput mouse;
	return mouse;
}