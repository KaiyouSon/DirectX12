#include "NewEngine/Gui/Header/HierarchyLayer.h"
#include "NewEngine/Gui/Header/SceneLayer.h"
#include "NewEngine/Gui/Header/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"

void HierarchyLayer::Initialize()
{
	size = { WIN_HALF_WIDTH / 2,670 };
	pos = { 0,0 };
}

static bool showMenu = false;
static bool isTest = false;
static bool isTest2 = false;
Vec2 menuWindowPos = { 0,0 };

void HierarchyLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Hierarchy", nullptr, window_flags);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::BeginMenu("Object 3D"))
			{
				if (ImGui::MenuItem("Cube"))	ObjectManager::GetInstance()->CreateCube();
				if (ImGui::MenuItem("Sphere"))	ObjectManager::GetInstance()->CreateSphere();
				if (ImGui::MenuItem("Monkey"))	ObjectManager::GetInstance()->CreateMonkey();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

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
