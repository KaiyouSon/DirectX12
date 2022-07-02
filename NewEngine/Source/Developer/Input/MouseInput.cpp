#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Input/MouseInput.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include <cassert>

void MouseInput::Initialize()
{
	HRESULT result;

	// �}�E�X�f�o�C�X�̐���
	result = Input::GetInstance()->GetDirectInput()->
		CreateDevice(GUID_SysMouse, &mouse, nullptr);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = mouse->SetDataFormat(&c_dfDIMouse2); // �g��8�{�^���܂�
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = mouse->SetCooperativeLevel(
		RenderWindow::GetInstance().GetHwnd(),
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
	ScreenToClient(RenderWindow::GetInstance().GetHwnd(), &tmpMousePos);
	mousePos.x = static_cast<float>(tmpMousePos.x);
	mousePos.y = static_cast<float>(tmpMousePos.y);
}

bool MouseInput::GetClick(const int& mouse)
{
	return mouseInput.rgbButtons[mouse] & (0x80);
}

bool MouseInput::GetClickTrigger(const int& mouse)
{
	return (mouseInput.rgbButtons[mouse] & (0x80)) &&
		!(oldMouseInput.rgbButtons[mouse] & (0x80));
}

bool MouseInput::GetClickReleased(const int& mouse)
{
	return !(mouseInput.rgbButtons[mouse] & (0x80)) &&
		(oldMouseInput.rgbButtons[mouse] & (0x80));
}

Vec2 MouseInput::GetMousePos()
{
	return mousePos;
}

float MouseInput::GetWheelVec()
{
	Vec3 vec = { (float)mouseInput.lX ,(float)mouseInput.lY ,(float)mouseInput.lZ };
	return vec.z;
}

MouseInput* MouseInput::GetInstance()
{
	static MouseInput* mouse = new MouseInput;
	return mouse;
}

void MouseInput::DestoryInstance()
{
	delete GetInstance();
}
