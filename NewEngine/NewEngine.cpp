#include "NewEngine/NewEngine.h"
#include "NewEngine/Header/Gui/GuiManager.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Developer/DeveloperManager.h"
#include "NewEngine/Header/DataOperator.h"
#include "NewEngine/Header/Developer/Object/Object2D/RenderTexture.h"
#include "NewEngine/Header/Developer/Component/Blend.h"
#include "NewEngine/main2.h"

#include <wrl.h>
using namespace Microsoft::WRL;

void NewEngineInit()
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif
	DataOperator::GetInstance()->Initialize();
	DataOperator::GetInstance()->LoadWindowData();

	RenderWindow::GetInstance().SetWindowTitle(
		DataOperator::GetInstance()->GetGameWindowTitleForStorage());
	RenderWindow::GetInstance().SetWindowSize(
		DataOperator::GetInstance()->GetGameWindowSizeForStorage().x,
		DataOperator::GetInstance()->GetGameWindowSizeForStorage().y);
#ifdef _DEBUG
	RenderWindow::GetInstance().SetWindowTitle("NewEngine");
	RenderWindow::GetInstance().SetWindowSize(1920, 1010);
#endif
	RenderWindow::GetInstance().CreateGameWindow();
	renderBase->Initialize();
#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> infoQuene;
	if (SUCCEEDED(renderBase->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQuene))))
	{
		infoQuene->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);	// やばいエラー一時に止まる
		infoQuene->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);		// エラー時に止まる
		//infoQuene->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);		// エラー時に止まる
		
	}
#endif

	DeveloperManager::GetInstance()->Initialize();
#ifdef _DEBUG
	GuiManager::GetInstance()->Initialize();
#endif
}
void NewEngineUpda()
{
	DeveloperManager::GetInstance()->Update();
#ifdef _DEBUG
	GuiManager::GetInstance()->Update();
#endif
}
void NewEnginePreDraw()
{
	sceneViewTexture->PreDrawScene();
}
void NewEneineDraw()
{
	// 背景描画
	DeveloperManager::GetInstance()->Draw2DToBack();
	// モデル描画
	DeveloperManager::GetInstance()->Draw3D();
	// 前景描画
	DeveloperManager::GetInstance()->Draw2DToForward();
}
void NewEnginePostDraw()
{
	sceneViewTexture->PostDrawScene();

	renderBase->PreDraw();
	Draw2D();
#ifdef _DEBUG
	GuiManager::GetInstance()->Draw();
#endif

	renderBase->GetInstance()->PostDraw();
}
void NewEngineEnd()
{
	// ウィンドウクラスを登録解除
	RenderWindow::GetInstance().TerminateGameWindow();

	//ComPtr<ID3D12Device> tmpDevice = RenderBase::GetInstance()->GetDevice().Get();
#ifdef _DEBUG
	GuiManager::DestroyInstance();
#endif

	DeveloperManager::DestroyInstance();
	renderBase->DestroyInstance();
	DataOperator::DestroyInstance();

	//ID3D12DebugDevice* debugInterface;
	//if (SUCCEEDED(tmpDevice.Get()->QueryInterface(&debugInterface)))
	//{
	//	debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
	//	debugInterface->Release();
	//}
}

bool ProcessMessage()
{
	//ウインドウズのメッセージを処理する
	if (RenderWindow::GetInstance().ProcessMessage() == WM_QUIT) return true;
	return false;
}
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT)
{
	RenderWindow::GetInstance().SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
}
void SetWindowTitle(const std::string TITLE)
{
	RenderWindow::GetInstance().SetWindowTitle(TITLE);
}
void SetBackgroundColor(float Red, float Green, float Blue)
{
	//RenderBase::GetInstance()->clearColor[0] = Red / 255;
	//RenderBase::GetInstance()->clearColor[1] = Green / 255;
	//RenderBase::GetInstance()->clearColor[2] = Blue / 255;
}
