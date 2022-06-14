#include "MyGUI.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ShaderResourceView.h"
#include "Util.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx12.h"
#include "ImGUI/imgui_impl_win32.h"

struct FrameContext
{
	ID3D12CommandAllocator* CommandAllocator;
	UINT64                  FenceValue;
};

static int const                    NUM_FRAMES_IN_FLIGHT = 3;
static FrameContext                 g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};

void MyGUI::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(NewEngineWindow::GetInstance().GetHwnd());
	ImGui_ImplDX12_Init(
		NewEngineBase::GetInstance()->GetDevice().Get(),
		NUM_FRAMES_IN_FLIGHT,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		ShaderResourceView::GetInstance()->GetSrvHeap().Get(),
		ShaderResourceView::GetInstance()->GetSrvHeap().Get()->GetCPUDescriptorHandleForHeapStart(),
		ShaderResourceView::GetInstance()->GetSrvHeap().Get()->GetGPUDescriptorHandleForHeapStart());
}

void MyGUI::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Inspector");
	ImGui::SetWindowPos(ImVec2(WIN_WIDTH - 300, 0));
	ImGui::SetWindowSize(ImVec2(300, WIN_HEIGHT));
	if (ImGui::BeginMenu("Transform"))
	{
		ImGui::Text("Hello ImGui!\n");
		ImGui::Text("Hello2 ImGui!");
		ImGui::EndMenu();
	}


	static char buf[256] = "aaa";
	if (ImGui::InputText("string", buf, 256)) {
		printf("InputText\n");
	}

	bool show_demo_window = true;
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::End();
}

void MyGUI::Draw()
{
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(
		ImGui::GetDrawData(), NewEngineBase::GetInstance()->GetCommandList().Get());
}

MyGUI* MyGUI::GetInstance()
{
	static MyGUI* gui = new MyGUI;
	return gui;
}

void MyGUI::DestroyInstance()
{
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	delete GetInstance();
}
