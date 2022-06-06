#include "JoypadInput.h"

void JoypadInput::Initialize()
{
}

void JoypadInput::Update()
{
}

JoypadInput& JoypadInput::GetInstance()
{
	static JoypadInput pad;
	return pad;
}
