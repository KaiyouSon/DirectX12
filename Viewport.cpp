#include "Viewport.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"

extern NewEngineBase* newEngine;
extern NewEngineWindow* newEngineWin;

void Viewport::Update()
{
	//----------------------- �r���[�|�[�g�̐ݒ�R�}���h -----------------------//
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = newEngineWin->GetWinWidth();
	viewport.Height = newEngineWin->GetWinHeight();
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	newEngine->GetCommandList()->RSSetViewports(1, &viewport);
}
