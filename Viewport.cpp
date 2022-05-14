#include "Viewport.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"

void Viewport::Update()
{
	//----------------------- �r���[�|�[�g�̐ݒ�R�}���h -----------------------//
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = NewEngineWindow::GetInstance().GetWinWidth();
	viewport.Height = NewEngineWindow::GetInstance().GetWinHeight();
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	NewEngineBase::GetInstance().GetCommandList()->RSSetViewports(1, &viewport);
}
