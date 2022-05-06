#include "ScissorRectangle.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"

extern NewEngineBase* newEngine;
extern NewEngineWindow* newEngineWin;

void ScissorRectangle::Update()
{
	//------------------------ �V�U�[��`�̐ݒ�R�}���h ------------------------//
	// �V�U�[��`
	D3D12_RECT scissorRect{};
	scissorRect.left = 0; // �؂蔲�����W��
	scissorRect.right = scissorRect.left + newEngineWin->GetWinWidth(); // �؂蔲�����W�E
	scissorRect.top = 0; // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + newEngineWin->GetWinHeight(); // �؂蔲�����W��
	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	newEngine->GetCommandList()->RSSetScissorRects(1, &scissorRect);
}
