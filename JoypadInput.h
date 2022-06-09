#pragma once
#include <dinput.h>
#include <wrl.h>
#include "MathUtil.h"
#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_L1 4
#define BUTTON_R1 5
#define BUTTON_BACK 6
#define BUTTON_START 7

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

	static JoypadInput& GetInstance();

private:
	JoypadInput() = default;
	~JoypadInput() = default;

	JoypadInput(const JoypadInput&) = delete;
	JoypadInput& operator=(const JoypadInput&) = delete;
	JoypadInput(const JoypadInput&&) = delete;
	JoypadInput& operator=(const JoypadInput&&) = delete;
};