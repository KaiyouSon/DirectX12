#include "Header/GUI/MainLayer.h"
#include "Header/GUI/ProjectLayer.h"
#include "Header/MyGUI.h"
#include "Header/Util.h"

void MainLayer::Initialize()
{
	size = Vec2(WIN_WIDTH, WIN_HEIGHT);
	pos = Vec2(0, 0);
}

void MainLayer::Update()
{
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar |				// タイトルバー表示しない
		ImGuiWindowFlags_NoResize |					// サイズ変更しない
		ImGuiWindowFlags_NoMove |					// 座標変更しない
		ImGuiWindowFlags_MenuBar |					// メニューバー表示
		ImGuiWindowFlags_NoBringToFrontOnFocus |	//クリックしたら最前面に表示しない
		ImGuiWindowFlags_NoCollapse;				// 折り畳みしない

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("MainView", nullptr, window_flags);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Assets"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("GameObject"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Component"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	//ImGui::SameLine(8);
	ImGui::Button("CameraMove", { 32, 24 });
	ImGui::SameLine(40);
	ImGui::Button("CameraRot", { 32, 24 });
	ImGui::SameLine(72);	
	ImGui::Button("CameraScale", { 32, 24 });
	ImGui::End();

}

Vec2 MainLayer::GetPos()
{
	return pos;
}

Vec2 MainLayer::GetSize()
{
	return size;
}

MainLayer* MainLayer::GetInstance()
{
	static MainLayer* MainLayer = new class::MainLayer;
	return MainLayer;
}

void MainLayer::DestroyInstance()
{
	delete GetInstance();
}
