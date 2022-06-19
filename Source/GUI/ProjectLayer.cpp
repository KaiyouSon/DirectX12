#include "Header/GUI/ProjectLayer.h"
#include "Header/MyGUI.h"
#include "Header/Util.h"
#include <filesystem>
using namespace std::filesystem;

void ProjectLayer::Initialize()
{
	size = { 1440,340 };
	pos = { 0,WIN_HEIGHT - size.y };
}

void ProjectLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Project", nullptr, window_flags);



	static float pading = 16;		// 間隔の幅
	static float buttonSize = 128;	// ボタンの大きさ
	float cellSize = buttonSize + pading;	// セル何個分？
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int padingCount = panelWidth / cellSize;
	if (padingCount < 1) padingCount = 1;

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Setting"))
		{
			ImGui::SliderFloat("Button Size", &buttonSize, 32, 256);
			ImGui::SliderFloat("Pading", &pading, 0, 32);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Columns(padingCount, 0, false);
	// ディレクトリ内のファイルを見る
	for (const directory_entry& cppfile : directory_iterator("."))
	{
		std::string filenameString = cppfile.path().filename().string();
		if (filenameString.substr(filenameString.length() - 3) == "cpp")
		{
			ImGui::Button(filenameString.c_str(), { buttonSize,buttonSize });
			ImGui::Text(filenameString.c_str());
			ImGui::NextColumn();
		}
		else continue;
	}
	ImGui::Columns(1);

	ImGui::End();
}

Vec2 ProjectLayer::GetPos()
{
	return pos;
}

Vec2 ProjectLayer::GetSize()
{
	return size;
}

ProjectLayer* ProjectLayer::GetInstance()
{
	static ProjectLayer* projectLayer = new ProjectLayer;
	return projectLayer;
}

void ProjectLayer::DestroyInstance()
{
	delete GetInstance();
}
