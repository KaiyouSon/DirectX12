#include "Header/ScissorRectangle.h"
#include "NewEngine/Render/Header/NewEngineBase.h"
#include "Header/NewEngineWindow.h"

void ScissorRectangle::Update()
{
	//------------------------ �V�U�[��`�̐ݒ�R�}���h ------------------------//
	// �V�U�[��`
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // �؂蔲�����W��
	scissorRect.right = scissorRect.left + 
		NewEngineWindow::GetInstance().GetWinWidth(); // �؂蔲�����W�E
	scissorRect.top = 0; // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + 
		NewEngineWindow::GetInstance().GetWinHeight(); // �؂蔲�����W��
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	NewEngineBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
