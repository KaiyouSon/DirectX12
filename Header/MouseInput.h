#pragma once
#include <dinput.h>
#include <wrl.h>
#include "Header/MathUtil.h"

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
	bool GetMouseLeft();
	bool GetMouseLeftTrigger();
	bool GetMouseLeftReleased();
	bool GetMouseRight();
	bool GetMouseRightTrigger();
	bool GetMouseRightReleased();
	bool GetMouseWheel();
	bool GetMouseWheelTrigger();
	bool GetMouseWheelReleased();
	Vec2 GetMousePos();
	Vec3 GetMouseVelocity();

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