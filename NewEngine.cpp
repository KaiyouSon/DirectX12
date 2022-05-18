#include "NewEngine.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ShaderResourceView.h"
#include "ShaderCompiler.h"
#include "GraphicsPipeline2D.h"
#include "GraphicsPipeline3D.h"
#include "GraphicsCommand.h"
#include "DepthBuffer.h"
#include "RootSignature.h"
#include "Util.h"

GraphicsCommand* graphicsCmd = new GraphicsCommand;

void NewEngineInit()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif

	// WindowsAPI初期化
	NewEngineWindow::GetInstance().CreateGameWindow();

	// DirectXの初期化処理
	NewEngineBase::GetInstance().Initialize();

	// 深度バッファの初期化
	DepthBuffer::GetInstance().Initialize();

	// シェーダーリソースビューの初期化
	ShaderResourceView::GetInstance().Initialize();

	// シェーダファイルの読み込みとコンパイル
	ShaderCompiler::GetInstance().BasicVSCompile();
	ShaderCompiler::GetInstance().BasicPSCompile();

	// ルートシグネチャの初期化
	RootSignature::GetInstance().Initialize();

	// グラフィックスパイプラインの初期化
	GraphicsPipeline2D::GetInstance().Initialize();
	GraphicsPipeline3D::GetInstance().Initialize();
}

void NewEngineEnd()
{
	// ウィンドウクラスを登録解除
	NewEngineWindow::GetInstance().TerminateGameWindow();

	delete graphicsCmd;
}

void ProcessMessage()
{
	//ウインドウズのメッセージを処理する
	NewEngineWindow::GetInstance().ProcessMessage();
}

void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT)
{
	NewEngineWindow::GetInstance().SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
}

void SetWindowTitle(const wchar_t* TITLE)
{
	NewEngineWindow::GetInstance().SetWindowTitle(TITLE);
}

bool CloseWindow()
{
	if (NewEngineWindow::GetInstance().GetProcessMessage() == WM_QUIT)
		return true;

	return false;
}

void SetBackgroundColor(float Red, float Green, float Blue)
{
	graphicsCmd->SetBackgroundColor(Red, Green, Blue);
}

void NewEnginePreDraw()
{
	graphicsCmd->PreDraw();
}

void NewEngineSetDraw3D()
{
	graphicsCmd->Draw3D();
}

void NewEngineSetDraw2D()
{
	graphicsCmd->Draw2D();
}

void NewEnginePostDraw()
{
	graphicsCmd->PostDraw();
}