#include "Header/GUI/HierarchyLayer.h"
#include "Header/GUI/SceneLayer.h"
#include "Header/MyGUI.h"
#include "Header/Util.h"

void HierarchyLayer::Initialize()
{
	size = { WIN_HALF_WIDTH / 2,670 };
	pos = { 0,0 };
}

static bool showMenu = false;
Vec2 menuWindowPos = { 0,0 };

void HierarchyLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Hierarchy", nullptr, window_flags |= ImGuiWindowFlags_NoCollapse);

	ImGui::End();
}

Vec2 HierarchyLayer::GetPos()
{
	return pos;
}

Vec2 HierarchyLayer::GetSize()
{
	return size;
}

HierarchyLayer* HierarchyLayer::GetInstance()
{
	static HierarchyLayer* hierarchyLayer = new HierarchyLayer;
	return hierarchyLayer;
}

void HierarchyLayer::DestroyInstance()
{
	delete GetInstance();
}
