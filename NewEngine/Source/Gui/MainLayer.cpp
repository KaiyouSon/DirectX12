#include "NewEngine/Header/Gui/MainLayer.h"
#include "NewEngine/Header/Gui/ProjectLayer.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"

void MainLayer::Initialize()
{
	size = Vec2(WIN_WIDTH, WIN_HEIGHT);
	pos = Vec2(0, 0);
}

void MainLayer::Update()
{
	static bool dockspaceOpen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar |				// タイトルバー表示しない
		ImGuiWindowFlags_NoResize |					// サイズ変更しない
		ImGuiWindowFlags_NoMove |					// 座標変更しない
		ImGuiWindowFlags_MenuBar |					// メニューバー表示
		ImGuiWindowFlags_NoBringToFrontOnFocus |	// クリックしたら最前面に表示しない
		ImGuiWindowFlags_NoCollapse |				// 折り畳みしない
		ImGuiWindowFlags_NoNavFocus;

	// ウィンドウの設定
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ShowMenuBar();

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::Begin("Test");
	ImGui::Text("Is Test Now");
	ImGui::End();
}

void MainLayer::ShowMenuBar()
{
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
