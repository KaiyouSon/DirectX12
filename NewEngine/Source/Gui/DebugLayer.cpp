#include "NewEngine/Header/Gui/DebugLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"

void DebugLayer::Initialize()
{
	size = { 960,111 };
	pos = { WIN_HALF_WIDTH / 2,0 };
}

void DebugLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("User", nullptr, window_flags);


	ImGui::End();
}

Vec2 DebugLayer::GetPos()
{
	return pos;
}

Vec2 DebugLayer::GetSize()
{
	return size;
}

DebugLayer* DebugLayer::GetInstance()
{
	static DebugLayer* DebugLayer = new class::DebugLayer;
	return DebugLayer;
}

void DebugLayer::DestroyInstance()
{
	delete GetInstance();
}
