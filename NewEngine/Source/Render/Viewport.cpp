#include "NewEngine/Header/Render/Viewport.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Gui/SceneLayer.h"

void Viewport::Update()
{
	//----------------------- �r���[�|�[�g�̐ݒ�R�}���h -----------------------//
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = RenderWindow::GetInstance().GetWinWidth();
	viewport.Height = RenderWindow::GetInstance().GetWinHeight();
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

#ifdef _DEBUG
	viewport.Width = SceneLayer::GetInstance()->GetSize().x;
	viewport.Height = SceneLayer::GetInstance()->GetSize().y;
	viewport.TopLeftX = SceneLayer::GetInstance()->GetPos().x;
	viewport.TopLeftY = SceneLayer::GetInstance()->GetPos().y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
#endif

	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	RenderBase::GetInstance()->GetCommandList()->RSSetViewports(1, &viewport);
}
