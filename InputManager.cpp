#include <cassert>
#include "InputManager.h"
#include "NewEngineWindow.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void InputManager::Initialize()
{
	HRESULT result;

	// DirectInputÇÃèâä˙âª
	result = DirectInput8Create(
		NewEngineWindow::GetInstance().GetHInstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	JoypadInput::GetInstance().Initialize();
	KeyBoardInput::GetInstance().Initialize();
	MouseInput::GetInstance().Initialize();
}

void InputManager::Update()
{
	JoypadInput::GetInstance().Update();
	KeyBoardInput::GetInstance().Update();
	MouseInput::GetInstance().Update();
}

Microsoft::WRL::ComPtr<IDirectInput8> InputManager::GetDirectInput()
{
	return directInput;
}

JoypadInput& InputManager::PadInstance()
{
	return JoypadInput::GetInstance();
}

KeyBoardInput& InputManager::KeyInstance()
{
	return KeyBoardInput::GetInstance();
}

MouseInput& InputManager::MouseInstance()
{
	return MouseInput::GetInstance();
}

InputManager& InputManager::GetInstance()
{
	static InputManager input;
	return input;
}