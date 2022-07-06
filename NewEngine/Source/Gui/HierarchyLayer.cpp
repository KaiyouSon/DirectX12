#include "NewEngine/Header/Gui/HierarchyLayer.h"
#include "NewEngine/Header/Gui/InspectorLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
using namespace std;

void HierarchyLayer::Initialize()
{
	size = { WIN_HALF_WIDTH / 2,670 };
	pos = { 0,0 };

	currentObjNode = -1, oldObjNode = -1;
	currentSprNode = -1, oldSprNode = -1;
}
void HierarchyLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Hierarchy", nullptr, window_flags);

	// メニューバー
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ShowMenuContest();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ShowObjectList();
	ShowSpriteList();

	// 右クリックしたら
	if (ImGui::GetMouseClickedCount(1))
		ImGui::OpenPopup("RightClick");

	if (ImGui::BeginPopup("RightClick"))
	{
		ShowMenuContest();
		ImGui::EndPopup();
	}

	ImGui::End();
}

void HierarchyLayer::ShowMenuContest()
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

}
void HierarchyLayer::ShowObjectList()
{
	auto objList = ObjectManager::GetInstance()->GetObjectList();

	// オブジェクト一覧の表示
	for (int i = 0; i < objList.size(); i++)
	{
		// 名前の処理（タイトルの）
		string  nameStr = objList[i]->GetName();
		const char* nameChar = {};
		if (objList[i]->GetName().size() <= 0)	nameChar = "##";
		else nameChar = nameStr.c_str();

		if (ImGui::TreeNode(nameChar))
		{
			if (key->GetKeyTrigger(DIK_DELETE))
			{
				ObjectManager::GetInstance()->DestroyModel(objList[currentObjNode]);
				currentObjNode = -1;
			}
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			oldObjNode = currentObjNode;
			currentObjNode = i;

			currentSprNode = -1, oldSprNode = -1;
		}

		if (currentObjNode >= 0)
		{
			if (currentObjNode != oldObjNode)
			{
				if (currentObjNode >= 0)	objList[currentObjNode]->SetisShowDataToInspector(true);
				if (oldObjNode >= 0)		objList[oldObjNode]->SetisShowDataToInspector(false);
			}
		}
		else objList[i]->SetisShowDataToInspector(false);
	}
}
void HierarchyLayer::ShowSpriteList()
{
	auto sprList = ObjectManager::GetInstance()->GetSpriteList();

	// スプライト一覧の表示
	for (int i = 0; i < sprList.size(); i++)
	{
		// 名前の処理（タイトルの）
		string  nameStr = sprList[i]->GetName();
		const char* nameChar = {};
		if (sprList[i]->GetName().size() <= 0)	nameChar = "##";
		else nameChar = nameStr.c_str();

		if (ImGui::TreeNode(nameChar))
		{
			if (key->GetKeyTrigger(DIK_DELETE))
			{
				ObjectManager::GetInstance()->DestroySprite(sprList[currentObjNode]);
				currentSprNode = -1;
			}
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			oldSprNode = currentSprNode;
			currentSprNode = i;

			currentObjNode = -1, oldObjNode = -1;
		}

		if (currentSprNode >= 0)
		{
			if (currentSprNode != oldSprNode)
			{
				if (currentSprNode >= 0)	sprList[currentSprNode]->SetisShowDataToInspector(true);
				if (oldSprNode >= 0)		sprList[oldSprNode]->SetisShowDataToInspector(false);
			}
		}
		else sprList[i]->SetisShowDataToInspector(false);
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
