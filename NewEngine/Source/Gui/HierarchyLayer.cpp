#include "NewEngine/Header/Gui/HierarchyLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"

void HierarchyLayer::Initialize()
{
	size = { WIN_HALF_WIDTH / 2,670 };
	pos = { 0,0 };
}
void HierarchyLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Hierarchy", nullptr, window_flags);

	ShowMenuBar();

	if (ImGui::CollapsingHeader("Object 3D")) ShowObjectList();
	if (ImGui::CollapsingHeader("Sprite 2D")) ShowSpriteList();

	ImGui::End();
}

void HierarchyLayer::ShowMenuBar()
{
	// メニューバー
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
			if (ImGui::MenuItem("Sprite 2D"))
			{
				ObjectManager::GetInstance()->CreateSprite();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void HierarchyLayer::ShowObjectList()
{
	// オブジェクトの表示
	for (auto tmpObjectList : ObjectManager::GetInstance()->GetObjectList())
	{
		if (ImGui::TreeNode(tmpObjectList->GetName().c_str()))
		{
			tmpObjectList->SetisShowDataToInspector(true);

			if (key->GetKeyTrigger(DIK_DELETE))
				ObjectManager::GetInstance()->DestroyModel(tmpObjectList);

			ImGui::TreePop();
		}
		else tmpObjectList->SetisShowDataToInspector(false);
	}
}

void HierarchyLayer::ShowSpriteList()
{
	// スプライトの表示
	for (auto tmpSpriteList : ObjectManager::GetInstance()->GetSpriteList())
	{
		if (ImGui::TreeNode(tmpSpriteList->GetName().c_str()))
		{
			tmpSpriteList->SetisShowDataToInspector(true);

			if (key->GetKeyTrigger(DIK_DELETE))
				ObjectManager::GetInstance()->DestroySprite(tmpSpriteList);

			ImGui::TreePop();
		}
		else tmpSpriteList->SetisShowDataToInspector(false);
	}
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
