#include "NewEngine/Header/Gui/UserLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
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
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("User", nullptr, window_flags);

	ImGui::Columns(6);
	ImGui::SameLine();
	ShowGameWindwoSetting();
	ImGui::NextColumn();
	ImGui::End();
}

void UserLayer::ShowGameWindwoSetting()
{
	DataOperator* dataOperator = DataOperator::GetInstance();
	if (ImGui::Button("Game Window", { 128, 32 }))
		ImGui::OpenPopup("GameWindwoSetting");

	if (ImGui::BeginPopupModal("GameWindwoSetting"))
	{
		// �^�C�g���̓���
		char title[50] = {};
		for (int i = 0; i < dataOperator->GetGameWindowTitleForStorage().size(); i++)
		{
			title[i] = dataOperator->GetGameWindowTitleForStorage().c_str()[i];
		}
		ImGui::Text("Title");
		ImGui::InputText("##", title, 50);

		// �T�C�Y�̓���
		int widthAndHeight[2] =
		{
			dataOperator->GetGameWindowSizeForStorage().x,
			dataOperator->GetGameWindowSizeForStorage().y,
		};
		ImGui::Text("Width & Height");
		ImGui::InputInt2("## ", widthAndHeight);

		// �ύX������������
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
