#include "NewEngine/Gui/Header/GuiManager.h"
#include "NewEngine/Gui/Header/MainLayer.h"
#include "NewEngine/Gui/Header/SceneLayer.h"
#include "NewEngine/Gui/Header/ProjectLayer.h"
#include "NewEngine/Gui/Header/HierarchyLayer.h"
#include "NewEngine/Gui/Header/DebugLayer.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx12.h"
#include "ImGUI/imgui_impl_win32.h"
#include "NewEngine/Render/Header/NewEngineBase.h"
#include "Header/NewEngineWindow.h"
#include "Header/ShaderResourceView.h"
#include "NewEngine/Header/Developer/Util/Util.h"

struct FrameContext
{
	ID3D12CommandAllocator* CommandAllocator;
	UINT64                  FenceValue;
};

static int const                    NUM_FRAMES_IN_FLIGHT = 3;
static FrameContext                 g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};

GuiManager::~GuiManager()
{
	SceneLayer::DestroyInstance();
	ProjectLayer::DestroyInstance();
	HierarchyLayer::DestroyInstance();
	DebugLayer::DestroyInstance();
}

void GuiManager::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(NewEngineWindow::GetInstance().GetHwnd());
	ImGui_ImplDX12_Init(
		NewEngineBase::GetInstance()->GetDevice().Get(),
		NUM_FRAMES_IN_FLIGHT,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		ShaderResourceView::GetInstance()->GetSrvHeap().Get(),
		ShaderResourceView::GetInstance()->GetSrvHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		ShaderResourceView::GetInstance()->GetSrvHeap().Get()->GetGPUDescriptorHandleForHeapStart());

	MainLayer::GetInstance()->Initialize();
	ProjectLayer::GetInstance()->Initialize();
	SceneLayer::GetInstance()->Initialize();
	HierarchyLayer::GetInstance()->Initialize();
	DebugLayer::GetInstance()->Initialize();
}

void GuiManager::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

	//MainLayer::GetInstance()->Update();
	SceneLayer::GetInstance()->Update();
	ProjectLayer::GetInstance()->Update();
	HierarchyLayer::GetInstance()->Update();
	DebugLayer::GetInstance()->Update();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	//bool show_demo_window = true;
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);
}

void GuiManager::Draw()
{
	ImGui::Render();
	// SRVヒープの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			ShaderResourceView::GetInstance()->GetSrvHeap().GetAddressOf());
	ImGui_ImplDX12_RenderDrawData(
		ImGui::GetDrawData(), NewEngineBase::GetInstance()->GetCommandList().Get());
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


