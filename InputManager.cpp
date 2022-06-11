#include <cassert>
#include "InputManager.h"
#include "NewEngineWindow.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

JoypadInput* pad = JoypadInput::GetInstance();
KeyBoardInput* key = KeyBoardInput::GetInstance();
MouseInput* mouse = MouseInput::GetInstance();

void InputManager::Initialize()
{
	HRESULT result;

	// DirectInput�̏�����
	result = DirectInput8Create(
		NewEngineWindow::GetInstance().GetHInstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	JoypadInput::GetInstance()->Initialize();
	KeyBoardInput::GetInstance()->Initialize();
	MouseInput::GetInstance()->Initialize();
}

void InputManager::Update()
{
	JoypadInput::GetInstance()->Update();
	KeyBoardInput::GetInstance()->Update();
	MouseInput::GetInstance()->Update();
}

Microsoft::WRL::ComPtr<IDirectInput8> InputManager::GetDirectInput()
{
	return directInput;
}

InputManager* InputManager::GetInstance()
{
	static InputManager* input = new InputManager;
	return input;
}

void InputManager::DestoryInstance()
{
	delete GetInstance();
}
