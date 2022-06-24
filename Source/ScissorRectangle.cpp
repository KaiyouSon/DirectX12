#include "Header/ScissorRectangle.h"
#include "NewEngine/Render/Header/NewEngineBase.h"
#include "Header/NewEngineWindow.h"

void ScissorRectangle::Update()
{
	//------------------------ シザー矩形の設定コマンド ------------------------//
	// シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // 切り抜き座標左
	scissorRect.right = scissorRect.left + 
		NewEngineWindow::GetInstance().GetWinWidth(); // 切り抜き座標右
	scissorRect.top = 0; // 切り抜き座標上
	scissorRect.bottom = scissorRect.top + 
		NewEngineWindow::GetInstance().GetWinHeight(); // 切り抜き座標下
	// シザー矩形設定コマンドを、コマンドリストに積む
	NewEngineBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
