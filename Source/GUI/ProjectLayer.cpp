#include "Header/GUI/ProjectLayer.h"
#include "Header/MyGUI.h"
#include "Header/Util.h"
#include "Header/DrawManager.h"
using namespace std::filesystem;

Texture cpptex;
Texture htex;

void ProjectLayer::Initialize()
{
	size = { 1440,340 };
	pos = { 0,WIN_HEIGHT - size.y };
	cpptex = LoadTexture("Resources/icon/cppFileTexture.png");
	htex = LoadTexture("Resources/icon/headerFileTexture.png");

	projectDirectroy = ".";	// �v���W�F�N�g�f�B���N�g���[
	currentDirectroy = projectDirectroy;
}

void ProjectLayer::Update()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::Begin("Project", nullptr, window_flags);

	static float pading = 16;		// �Ԋu�̕�
	static float buttonSize = 128;	// �{�^���̑傫��
	float cellSize = buttonSize + pading;	// �Z�������H
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

	if (currentDirectroy != path(projectDirectroy))
	{
		if (ImGui::Button("<-"))
		{
			currentDirectroy = currentDirectroy.parent_path();
		}
	}

	ImGui::Columns(padingCount, 0, false);

	// ���݂̃f�B���N�g�����̃t�@�C��������
	for (auto& directroy : directory_iterator(currentDirectroy))
	{
		const auto& path = directroy.path();					// �f�B���N�g���[�̃p�X�擾
		auto relativePath = relative(path, projectDirectroy);	// ���΃p�X
		std::string filenameString = relativePath.filename().string();	// �t�@�C���̖��O������̕ϊ�

		if (directroy.is_directory())
		{
			if (ImGui::Button(filenameString.c_str(), { buttonSize,buttonSize }))
			{
				currentDirectroy /= path.filename();
			}
			ImGui::Text(filenameString.c_str());
		}
		else
		{
			if (filenameString.substr(filenameString.length() - 4) == ".cpp")
			{
				ImGui::ImageButton((ImTextureID)cpptex.GetGpuHandle().ptr, { buttonSize,buttonSize });
				ImGui::Text(filenameString.c_str());
			}
			if (filenameString.substr(filenameString.length() - 2) == ".h")
			{
				ImGui::ImageButton((ImTextureID)htex.GetGpuHandle().ptr, { buttonSize,buttonSize });
				ImGui::Text(filenameString.c_str());
			}
			else
			{
				if (ImGui::Button(filenameString.c_str(), { buttonSize,buttonSize }));
				ImGui::Text(filenameString.c_str());
			}
		}
		ImGui::NextColumn();
	}
	ImGui::Columns(1);

	bool isDoubleClick = ImGui::IsMouseDoubleClicked(0);

	ImGui::Text("%d", isDoubleClick);

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
