#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
class HierarchyLayer : public ILayer
{
private:
	void ShowMenuBar();
	void ShowObjectList();
	void ShowSpriteList();

public:
	void Initialize() override;
	void Update() override;
	Vec2 GetPos() override;
	Vec2 GetSize() override;

	static HierarchyLayer* GetInstance();
	static void DestroyInstance();
private:
	HierarchyLayer() = default;
	~HierarchyLayer() = default;

	HierarchyLayer(const HierarchyLayer&) = delete;
	HierarchyLayer& operator=(const HierarchyLayer&) = delete;
	HierarchyLayer(const HierarchyLayer&&) = delete;
	HierarchyLayer& operator=(const HierarchyLayer&&) = delete;
};

