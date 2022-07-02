#pragma once
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <dinput.h>
#include <wrl.h>

class MouseInput
{
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouse;
	Vec2 mousePos;
	DIMOUSESTATE2 mouseInput;
	DIMOUSESTATE2 oldMouseInput;
public:
	void Initialize();
	void Update();

	// マウスの取得関連
	bool GetClick(const int& mouse);
	bool GetClickTrigger(const int& mouse);
	bool GetClickReleased(const int& mouse);

	Vec2 GetMousePos();
	float GetWheelVec();

	static MouseInput* GetInstance();
	static void DestoryInstance();
private:
	MouseInput() = default;
	~MouseInput() = default;

	MouseInput(const MouseInput&) = delete;
	MouseInput& operator=(const MouseInput&) = delete;
	MouseInput(const MouseInput&&) = delete;
	MouseInput& operator=(const MouseInput&&) = delete;
};