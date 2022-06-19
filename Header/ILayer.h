#pragma once
#include "ImGUI/imgui.h"
#include "MathUtil.h"
class ILayer
{
public:
	Vec2 pos;
	Vec2 size;
	virtual ~ILayer() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
};
