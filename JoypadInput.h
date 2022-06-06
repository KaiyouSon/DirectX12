#pragma once

class JoypadInput
{
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