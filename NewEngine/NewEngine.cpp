#include "NewEngine/NewEngine.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Render/Viewport.h"
#include "NewEngine/Header/Render/ScissorRectangle.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include <wrl.h>
using namespace Microsoft::WRL;

void NewEngineInit()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
	{
		debugController.Get()->EnableDebugLayer();
	}
#endif

	// WindowsAPI初期化
	RenderWindow::GetInstance().CreateGameWindow();

	// DirectXの初期化処理
	RenderBase::GetInstance()->Initialize();

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
	RenderWindow::GetInstance().TerminateGameWindow();

	//ComPtr<ID3D12Device> tmpDevice = RenderBase::GetInstance()->GetDevice().Get();
	// DirectXの破棄
	RenderBase::DestroyInstance();

	//ID3D12DebugDevice* debugInterface;

	//if (SUCCEEDED(tmpDevice.Get()->QueryInterface(&debugInterface)))
	//{
	//	debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
	//	debugInterface->Release();
	//}

	Input::GetInstance()->DestoryInstance();
}
void ProcessMessage()
{
	//ウインドウズのメッセージを処理する
	RenderWindow::GetInstance().ProcessMessage();
}
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT)
{
	RenderWindow::GetInstance().SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
}
void SetWindowTitle(const std::string TITLE)
{
	RenderWindow::GetInstance().SetWindowTitle(TITLE);
}
bool CloseWindow()
{
	if (RenderWindow::GetInstance().GetProcessMessage() == WM_QUIT)
		return true;

	return false;
}
void SetBackgroundColor(float Red, float Green, float Blue)
{
}
void NewEnginePreDraw()
{
	RenderBase::GetInstance()->PreDraw();
}
void NewEngineSetDraw3D()
{
	RenderBase::GetInstance()->Draw3D();
}
void NewEngineSetDraw2D()
{
	RenderBase::GetInstance()->Draw2D();
}
void NewEnginePostDraw()
{
	RenderBase::GetInstance()->PostDraw();
}