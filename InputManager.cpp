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

IDirectInput8* InputManager::GetDirectInput()
{
	return directInput;
}

KeyBoardInput& InputManager::Key()
{
	return KeyBoardInput::GetInstance();
}

MouseInput& InputManager::Mouse()
{
	return MouseInput::GetInstance();
}

InputManager& InputManager::GetInstance()
{
	static InputManager input;
	return input;
}
