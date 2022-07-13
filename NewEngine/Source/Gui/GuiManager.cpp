#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Gui/MainLayer.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include "NewEngine/Header/Gui/ProjectLayer.h"
#include "NewEngine/Header/Gui/HierarchyLayer.h"
#include "NewEngine/Header/Gui/UserLayer.h"
#include "NewEngine/Header/Gui/InspectorLayer.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx12.h"
#include "ImGUI/imgui_impl_win32.h"

static int const NUM_FRAMES_IN_FLIGHT = 3;

GuiManager::~GuiManager()
{
	MainLayer::DestroyInstance();
	SceneLayer::DestroyInstance();
	ProjectLayer::DestroyInstance();
	HierarchyLayer::DestroyInstance();
	UserLayer::DestroyInstance();
	InspectorLayer::DestroyInstance();
}

void GuiManager::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(RenderWindow::GetInstance().GetHwnd());
	ImGui_ImplDX12_Init(
		RenderBase::GetInstance()->GetDevice().Get(),
		NUM_FRAMES_IN_FLIGHT,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		RenderBase::GetInstance()->GetSrvDescHeap().Get(),
		RenderBase::GetInstance()->GetSrvDescHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		RenderBase::GetInstance()->GetSrvDescHeap().Get()->GetGPUDescriptorHandleForHeapStart());

	//MainLayer::GetInstance()->Initialize();
	ProjectLayer::GetInstance()->Initialize();
	SceneLayer::GetInstance()->Initialize();
	HierarchyLayer::GetInstance()->Initialize();
	UserLayer::GetInstance()->Initialize();
	InspectorLayer::GetInstance()->Initialize();
}

void GuiManager::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::NewFrame();

	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));


	//MainLayer::GetInstance()->Update();
	SceneLayer::GetInstance()->Update();
	ProjectLayer::GetInstance()->Update();
	HierarchyLayer::GetInstance()->Update();
	UserLayer::GetInstance()->Update();
	InspectorLayer::GetInstance()->Update();

	//ImGui::PopFont();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	//ImGui::Begin("TestWindow");
	//ImGui::Text("Test");
	//ImGui::End();

	//bool show_demo_window = true;
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
}

void GuiManager::Draw()
{
	ImGui::Render();
	// SRVヒープの設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			RenderBase::GetInstance()->GetSrvDescHeap().GetAddressOf());
	ImGui_ImplDX12_RenderDrawData(
		ImGui::GetDrawData(), RenderBase::GetInstance()->GetCommandList().Get());
}

GuiManager* GuiManager::GetInstance()
{
	static GuiManager* gui = new GuiManager;
	return gui;
}

void GuiManager::DestroyInstance()
{
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	delete GetInstance();
}


