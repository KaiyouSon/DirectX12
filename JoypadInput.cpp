#include "JoypadInput.h"
#include "NewEngineWindow.h"
#include "InputManager.h"
#include <cassert>

void JoypadInput::Initialize()
{
	//Input::GetInstance().GetDirectInput()->
	//	EnumDevices(
	//		DI8DEVCLASS_GAMECTRL,
	//		DeviceFindCallBack,
	//		joypad,
	//		DIEDFL_ATTACHEDONLY);

	//HRESULT result;
	//result = Input::GetInstance().GetDirectInput()->
	//	CreateDevice()
}

void JoypadInput::Update()
{
}


// デバイス発見時に実行される
BOOL CALLBACK JoypadInput::DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

JoypadInput& JoypadInput::GetInstance()
{
	static JoypadInput pad;
	return pad;
}