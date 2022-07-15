#include "NewEngine/Header/Gui/UserLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/DataOperator.h"

void UserLayer::Initialize()
{
	size = { 960,111 };
	pos = { WIN_HALF_WIDTH / 2,0 };
}

void UserLayer::Update()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
	//ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	//ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("User", nullptr, window_flags);

	ImGui::Columns(6);
	ImGui::SameLine();		ShowGameWindwoSetting();			ImGui::NextColumn();
	ImGui::SameLine(16);	ShowModelDataListSetting();			ImGui::NextColumn();
	ImGui::End();
}

void UserLayer::ShowGameWindwoSetting()
{
	DataOperator* dataOperator = DataOperator::GetInstance();
	if (ImGui::Button("Game Window", { 128, 32 }))
		ImGui::OpenPopup("GameWindowSetting");

	if (ImGui::BeginPopupModal("GameWindowSetting"))
	{
		// タイトルの入力
		char title[50] = {};
		for (int i = 0; i < dataOperator->GetGameWindowTitleForStorage().size(); i++)
		{
			title[i] = dataOperator->GetGameWindowTitleForStorage().c_str()[i];
		}
		ImGui::Text("Title");
		ImGui::InputText("##", title, 50);

		// サイズの入力
		int widthAndHeight[2] =
		{
			(int)dataOperator->GetGameWindowSizeForStorage().x,
			(int)dataOperator->GetGameWindowSizeForStorage().y,
		};
		ImGui::Text("Width & Height");
		ImGui::InputInt2("## ", widthAndHeight);

		// 変更を書き換える
		dataOperator->SetGameWindowParameter(
			title, { (float)widthAndHeight[0],(float)widthAndHeight[1] });

		if (ImGui::Button("Close"))
		{
			dataOperator->SaveWindowData();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}
void UserLayer::ShowModelDataListSetting()
{
	if (ImGui::Button("ModelDataList", { 128, 32 }))
		ImGui::OpenPopup("ModelDataSetting");

	if (ImGui::BeginPopupModal("ModelDataSetting"))
	{
		static char filePath[256] = {};
		static char modelDataName[50] = {};
		if (ImGui::CollapsingHeader("AddModelData"))
		{
			ImGui::InputText("FilePath", filePath, 256);

			static ModelData tmpModel;
			if (ImGui::Button("Search File")) tmpModel = LoadModel(filePath);

			if (tmpModel.GetTag() == "error")
			{
				ImGui::Text("Failed to load, Please check the FilePath");
			}
			if (tmpModel.vertices.empty() == false)
			{
				if (tmpModel.GetTag() != "error")
				{
					ImGui::Text("Loading is complete, Please enter the tag of the model data");
					ImGui::InputText("modelDataName", modelDataName, 50);

					if (ImGui::Button("Add"))
					{
						ImGui::Text("Added model data to ModelDataList");
						modelDataList->AddModelData(tmpModel, modelDataName);
					}
				}
			}
		}

		if (ImGui::CollapsingHeader("ModelDataList"))
		{
			for (int i = 0; i < modelDataList->GetList().size(); i++)
			{
				ImGui::MenuItem(modelDataList->GetList()[i].GetTag().c_str());
			}
		}

		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

Vec2 UserLayer::GetPos()
{
	return pos;
}
Vec2 UserLayer::GetSize()
{
	return size;
}

UserLayer* UserLayer::GetInstance()
{
	static UserLayer* UserLayer = new class::UserLayer;
	return UserLayer;
}
void UserLayer::DestroyInstance()
{
	delete GetInstance();
}
