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
#include "Viewport.h"
#include "ScissorRectangle.h"
#include "Util.h"

Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

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
	ShaderCompiler::GetInstance().BasicPSCompile2();

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

	delete viewport;
	delete scissorRectangle;
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
	GraphicsCommand::GetInstance().SetBackgroundColor(Red, Green, Blue);
}
void NewEnginePreDraw()
{
	GraphicsCommand::GetInstance().PreDraw();

	// ビューポートの処理
	viewport->Update();

	// シザー矩形の処理
	scissorRectangle->Update();
}
void NewEngineSetDraw3D()
{
	GraphicsCommand::GetInstance().Draw3D();
}
void NewEngineSetDraw2D()
{
	GraphicsCommand::GetInstance().Draw2D();
}
void NewEnginePostDraw()
{
	GraphicsCommand::GetInstance().PostDraw();
}