#include "ScissorRectangle.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"

extern NewEngineBase* newEngine;
extern NewEngineWindow* newEngineWin;

void ScissorRectangle::Update()
{
	//------------------------ シザー矩形の設定コマンド ------------------------//
	// シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // 切り抜き座標左
	scissorRect.right = scissorRect.left + newEngineWin->GetWinWidth(); // 切り抜き座標右
	scissorRect.top = 0; // 切り抜き座標上
	scissorRect.bottom = scissorRect.top + newEngineWin->GetWinHeight(); // 切り抜き座標下
	// シザー矩形設定コマンドを、コマンドリストに積む
	newEngine->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
