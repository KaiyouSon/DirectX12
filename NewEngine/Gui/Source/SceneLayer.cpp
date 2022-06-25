#include "NewEngine/Gui/Header/SceneLayer.h"
#include "NewEngine/Gui/Header/ProjectLayer.h"
#include "Header/MyGUI.h"
#include "NewEngine/Header/Developer/Util/Util.h"

void SceneLayer::Initialize()
{
	size = { 960,540 };
	pos = {
		WIN_HALF_WIDTH - size.x / 2,
		ProjectLayer::GetInstance()->GetPos().y - size.y };
}

void SceneLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y - 19));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y + 19));
	ImGui::Begin("SceneView", nullptr, window_flags |= ImGuiWindowFlags_NoCollapse);

	ImGui::End();
	ImGui::PopStyleColor();

}

Vec2 SceneLayer::GetPos()
{
	return pos;
}

Vec2 SceneLayer::GetSize()
{
	return size;
}

SceneLayer* SceneLayer::GetInstance()
{
	static SceneLayer* sceneLayer = new SceneLayer;
	return sceneLayer;
}

void SceneLayer::DestroyInstance()
{
	delete GetInstance();
}
