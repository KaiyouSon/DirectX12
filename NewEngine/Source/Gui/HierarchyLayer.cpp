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

	isCreateModel = false;
}
void HierarchyLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
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

	ImVec2 pos = ImGui::GetWindowPos();
	ImVec2 size = ImGui::GetWindowSize();

	// 右クリックしたら
	if (ImGui::GetMousePos().x > pos.x &&
		ImGui::GetMousePos().y > pos.y &&
		ImGui::GetMousePos().x < pos.x + size.x &&
		ImGui::GetMousePos().y < pos.y + size.y)
	{
		if (ImGui::GetMouseClickedCount(1))
			ImGui::OpenPopup("RightClick");
	}

	if (ImGui::BeginPopup("RightClick"))
	{
		ShowMenuContest();
		ImGui::EndPopup();
	}

	ShowCreateModelWindow();
	ImGui::End();
}
void HierarchyLayer::ShowMenuContest()
{
	if (ImGui::BeginMenu("Object 3D"))
	{
		if (ImGui::MenuItem("Cube"))	ObjectManager::GetInstance()->CreateCube();
		ImGui::Separator();
		if (ImGui::MenuItem("Sphere"))	ObjectManager::GetInstance()->CreateSphere();
		ImGui::Separator();
		if (ImGui::MenuItem("Monkey"))	ObjectManager::GetInstance()->CreateMonkey();
		ImGui::Separator();
		if (ImGui::MenuItem("Model"))	isCreateModel = true;

		ImGui::EndMenu();
	}
	ImGui::Separator();
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
			if (key->GetKeyTrigger(DIK_DELETE) &&
				currentSprNode == -1 && oldSprNode == -1)
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
			if (key->GetKeyTrigger(DIK_DELETE) &&
				currentObjNode == -1 && oldObjNode == -1)
			{
				ObjectManager::GetInstance()->DestroySprite(sprList[currentSprNode]);
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
void HierarchyLayer::ShowCreateModelWindow()
{
	if (isCreateModel == false) return;

	ImGui::OpenPopup("ModelDataSetting");

	if (ImGui::BeginPopupModal("ModelDataSetting"))
	{
		ImGui::Text("Please select the model data");
		if (ImGui::Button("    ", ImVec2(14, 14)))
			ImGui::OpenPopup("ModelDataList");

		if (ImGui::BeginPopup("ModelDataList"))
		{
			for (int i = 0; i < modelDataList->GetList().size(); i++)
			{
				if (ImGui::MenuItem(modelDataList->GetList()[i].GetTag().c_str()))
				{
					ObjectManager::GetInstance()->CreateModel(modelDataList->GetList()[i]);
					ImGui::CloseCurrentPopup();
				}
				ImGui::Separator();
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button("OK", ImVec2(128, 32)))
		{
			isCreateModel = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
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
