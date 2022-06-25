#include "NewEngine/Gui/Header/DebugLayer.h"
#include "NewEngine/Gui/Header/SceneLayer.h"
#include "NewEngine/Gui/Header/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"

void DebugLayer::Initialize()
{
	size = { 960,111 };
	pos = { WIN_HALF_WIDTH / 2,0 };
}

void DebugLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Debug", nullptr, window_flags |= ImGuiWindowFlags_NoCollapse);

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
