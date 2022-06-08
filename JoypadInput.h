#pragma once
#include <dinput.h>

class JoypadInput
{
private:
	IDirectInputDevice8* joypad;

	BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
public:
	void Initialize();
	void Update();

	static JoypadInput& GetInstance();

private:
	JoypadInput() = default;
	~JoypadInput() = default;

	JoypadInput(const JoypadInput&) = delete;
	JoypadInput& operator=(const JoypadInput&) = delete;
	JoypadInput(const JoypadInput&&) = delete;
	JoypadInput& operator=(const JoypadInput&&) = delete;
};