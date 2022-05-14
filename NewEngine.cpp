#include "NewEngine.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ShaderResourceView.h"
#include "ShaderCompiler.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"

#include "Util.h"

NewEngineBase* newEngine = new NewEngineBase;
ShaderResourceView* shaderResourceView = new ShaderResourceView;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
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
	newEngine->Initialize();

	// シェーダーリソースビューの初期化
	shaderResourceView->Initialize();

	// シェーダファイルの読み込みとコンパイル
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// グラフィックスパイプラインの初期化
	graphicsPipeline->Initialize();
}

void NewEngineEnd()
{
	// ウィンドウクラスを登録解除
	NewEngineWindow::GetInstance().TerminateGameWindow();

	delete newEngine;
	delete graphicsPipeline;
	delete graphicsCmd;
	delete shaderCompiler;
	delete shaderResourceView;
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

void SetBackgroundColor(int Red, int Green, int Blue)
{
	graphicsCmd->SetBackgroundColor(Red, Green, Blue);
}

void NewEnginePreDraw()
{
	graphicsCmd->PreUpdate();
}

void NewEnginePostDraw()
{
	graphicsCmd->PostUpdate();
}