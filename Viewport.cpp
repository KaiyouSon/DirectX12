#include "Viewport.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"

extern NewEngineBase* newEngine;

void Viewport::Update()
{
	//----------------------- ビューポートの設定コマンド -----------------------//
	// ビューポート設定コマンド
	D3D12_VIEWPORT viewport{};
	viewport.Width = NewEngineWindow::GetInstance().GetWinWidth();
	viewport.Height = NewEngineWindow::GetInstance().GetWinHeight();
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// ビューポート設定コマンドを、コマンドリストに積む
	newEngine->GetCommandList()->RSSetViewports(1, &viewport);
}
