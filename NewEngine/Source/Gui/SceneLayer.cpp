#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/ProjectLayer.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Object2D/RenderTexture.h"
extern RenderTexture* sceneViewTexture;

void SceneLayer::Initialize()
{
	size = { 960,540 };
	pos = {
		WIN_HALF_WIDTH - size.x / 2,
		ProjectLayer::GetInstance()->GetPos().y - size.y };
}

void SceneLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("SceneView", nullptr, window_flags);
	ImGui::Image((ImTextureID)sceneViewTexture->GetRenderTexture()->GetGpuHandle().ptr, { 960,540 });
	ImGui::End();
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
