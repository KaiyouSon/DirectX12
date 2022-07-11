#pragma once
#include "NewEngine/Header/Developer/Math/Vec2.h"
#include <memory>

class Viewport
{
private:
	Vec2 leftTopPos;
	Vec2 size;
	float MinDepth;
	float MaxDepth;

public:
	void Update();

	void SetViewport(const Vec2& leftTopPos, const Vec2& size, float MinDepth = 0.0f, float MaxDepth = 1.0f);

	Vec2 GetLeftTopPos();
	Vec2 GetSize();
	float GetMinDepth();
	float GetMaxDepth();
};

extern std::unique_ptr<Viewport> viewport;

