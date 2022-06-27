#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
class DebugLayer : public ILayer
{
public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static DebugLayer* GetInstance();
	static void DestroyInstance();
private:
	DebugLayer() = default;
	~DebugLayer() = default;

	DebugLayer(const DebugLayer&) = delete;
	DebugLayer& operator=(const DebugLayer&) = delete;
	DebugLayer(const DebugLayer&&) = delete;
	DebugLayer& operator=(const DebugLayer&&) = delete;
};

