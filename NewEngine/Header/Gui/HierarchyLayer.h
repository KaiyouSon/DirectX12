#pragma once
#include "NewEngine/Header/Gui/ILayer.h"
#include "NewEngine//Header/Developer/Object/Other/ObjectManager.h"
class HierarchyLayer : public ILayer
{
private:
	int currentObjNode;
	int oldObjNode;
	int currentSprNode;
	int oldSprNode;

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

