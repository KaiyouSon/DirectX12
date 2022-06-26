#include "Header/NewEngine.h"
#include "NewEngine/Header/Render/NewEngineBase.h"
#include "Header/NewEngineWindow.h"
#include "Header/ShaderResourceView.h"
#include "Header/ShaderCompiler.h"
#include "Header/GraphicsPipeline2D.h"
#include "Header/GraphicsPipeline3D.h"
#include "Header/GraphicsCommand.h"
#include "Header/DepthBuffer.h"
#include "Header/RootSignature.h"
#include "Header/Viewport.h"
#include "Header/ScissorRectangle.h"

#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include <wrl.h>
using namespace Microsoft::WRL;

Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

void NewEngineInit()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf())))) {
		debugController.Get()->EnableDebugLayer();
	}
#endif

	// WindowsAPI初期化
	NewEngineWindow::GetInstance().CreateGameWindow();

	// DirectXの初期化処理
	NewEngineBase::GetInstance()->Initialize();

	// 深度バッファの初期化
	DepthBuffer::GetInstance()->Initialize();

	// シェーダーリソースビューの初期化
	ShaderResourceView::GetInstance()->Initialize();

	// シェーダファイルの読み込みとコンパイル
	ShaderCompiler::GetInstance()->BasicVSCompile();
	ShaderCompiler::GetInstance()->BasicPSCompile();
	ShaderCompiler::GetInstance()->BasicPSCompile2();

	// ルートシグネチャの初期化
	RootSignature::GetInstance()->Initialize();

	// グラフィックスパイプラインの初期化
	GraphicsPipeline2D::GetInstance()->Initialize();
	GraphicsPipeline3D::GetInstance()->Initialize();

	// Inputの初期化
	Input::GetInstance()->Initialize();
}
void NewEngineUpda()
{
	// Inputの更新処理
	Input::GetInstance()->Update();
}
void NewEngineEnd()
{
	// ウィンドウクラスを登録解除
	NewEngineWindow::GetInstance().TerminateGameWindow();

	// 深度バッファの破棄
	DepthBuffer::DestroyInstance();

	// シェーダーリソースビューの破棄
	ShaderResourceView::DestroyInstance();

	// シェーダーコンパイラーの破棄
	ShaderCompiler::DestroyInstance();

	// ルートシグネチャの破棄
	RootSignature::DestroyInstance();

	// グラフィックスパイプラインの破棄
	GraphicsPipeline2D::DestroyInstance();
	GraphicsPipeline3D::DestroyInstance();

	//ComPtr<ID3D12Device> tmpDevice = NewEngineBase::GetInstance()->GetDevice().Get();
	// DirectXの破棄
	NewEngineBase::DestroyInstance();

	//ID3D12DebugDevice* debugInterface;

	//if (SUCCEEDED(tmpDevice.Get()->QueryInterface(&debugInterface)))
	//{
	//	debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
	//	debugInterface->Release();
	//}

	Input::GetInstance()->DestoryInstance();

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
void SetWindowTitle(const std::string TITLE)
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