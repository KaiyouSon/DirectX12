#pragma once
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <dinput.h>
#include <wrl.h>

class JoypadInput
{
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> joypad;
	DIJOYSTATE2 padInput;
	DIJOYSTATE2 oldPadInput;

	static BOOL CALLBACK DeviceFindCallBack(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
public:
	void Initialize();
	void Update();

	bool GetButton(const int& buttonNumber);
	bool GetButtonTrigger(const int& buttonNumber);
	bool GetButtonReleased(const int& buttonNumber);
	Vec2 GetLeftStickParam();
	Vec2 GetLeftStickVec();
	Vec2 GetRightStickParam();
	Vec2 GetRightStickVec();

	static JoypadInput* GetInstance();
	static void DestoryInstance();

private:
	JoypadInput() = default;
	~JoypadInput() = default;

	JoypadInput(const JoypadInput&) = delete;
	JoypadInput& operator=(const JoypadInput&) = delete;
	JoypadInput(const JoypadInput&&) = delete;
	JoypadInput& operator=(const JoypadInput&&) = delete;
};