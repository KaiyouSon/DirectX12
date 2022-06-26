#include "Header/Viewport.h"
#include "NewEngine/Header/Render/NewEngineBase.h"
#include "Header/NewEngineWindow.h"
#include "NewEngine/Gui/Header/SceneLayer.h"

void Viewport::Update()
{
	//----------------------- �r���[�|�[�g�̐ݒ�R�}���h -----------------------//
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = SceneLayer::GetInstance()->GetSize().x;
	viewport.Height = SceneLayer::GetInstance()->GetSize().y;
	viewport.TopLeftX = SceneLayer::GetInstance()->GetPos().x;
	viewport.TopLeftY = SceneLayer::GetInstance()->GetPos().y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	NewEngineBase::GetInstance()->GetCommandList()->RSSetViewports(1, &viewport);
}
