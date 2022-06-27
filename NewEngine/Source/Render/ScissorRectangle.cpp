#include "NewEngine/Header/Render/ScissorRectangle.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"

void ScissorRectangle::Update()
{
	//------------------------ シザー矩形の設定コマンド ------------------------//
	// シザー矩形
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // 切り抜き座標左
	scissorRect.right = scissorRect.left + 
		RenderWindow::GetInstance().GetWinWidth(); // 切り抜き座標右
	scissorRect.top = 0; // 切り抜き座標上
	scissorRect.bottom = scissorRect.top + 
		RenderWindow::GetInstance().GetWinHeight(); // 切り抜き座標下
	// シザー矩形設定コマンドを、コマンドリストに積む
	RenderBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
