#include <cassert>
#include "Input.h"
#include "NewEngineWindow.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize()
{
	HRESULT result;

	// DirectInputÇÃèâä˙âª
	result = DirectInput8Create(
		NewEngineWindow::GetInstance().GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	KeyBoardInput::GetInstance().Initialize();
	MouseInput::GetInstance().Initialize();
}

void Input::Update()
{
	KeyBoardInput::GetInstance().Update();
	MouseInput::GetInstance().Update();
}

IDirectInput8* Input::GetDirectInput()
{
	return directInput;
}

KeyBoardInput& Input::Key()
{
	return KeyBoardInput::GetInstance();
}

MouseInput& Input::Mouse()
{
	return MouseInput::GetInstance();
}

Input& Input::GetInstance()
{
	static Input input;
	return input;
}
