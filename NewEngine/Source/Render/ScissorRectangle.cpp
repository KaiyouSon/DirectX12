#include "NewEngine/Header/Render/ScissorRectangle.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"

void ScissorRectangle::Update()
{
	//------------------------ �V�U�[��`�̐ݒ�R�}���h ------------------------//
	// �V�U�[��`
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // �؂蔲�����W��
	scissorRect.right = scissorRect.left + 
		RenderWindow::GetInstance().GetWinWidth(); // �؂蔲�����W�E
	scissorRect.top = 0; // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + 
		RenderWindow::GetInstance().GetWinHeight(); // �؂蔲�����W��
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	RenderBase::GetInstance()->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
