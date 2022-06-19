#pragma once
#include "Header/MathUtil.h"
#include "ImGUI/imgui.h"
class ILayer
{
protected:
	Vec2 pos;
	Vec2 size;

	virtual ~ILayer() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual Vec2 GetPos() = 0;
	virtual Vec2 GetSize() = 0;
};