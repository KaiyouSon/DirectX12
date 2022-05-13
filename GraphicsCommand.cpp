#include "GraphicsCommand.h"
#include "NewEngineBase.h"
#include "GraphicsPipeline.h"
#include "Viewport.h"
#include "ScissorRectangle.h"
#include <cassert>

extern NewEngineBase* newEngine;
extern GraphicsPipeline* graphicsPipeline;
Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;


GraphicsCommand::~GraphicsCommand()
{
	delete viewport;
	delete scissorRectangle;
}

void GraphicsCommand::PreUpdate()
{
	//---------------------- ���\�[�X�o���A�̕ύX�R�}���h ----------------------//
	// �o�b�N�o�b�t�@�̔ԍ����擾�i2�Ȃ̂�0�Ԃ�1�ԁj
	UINT bbIndex = newEngine->GetSwapChain()->GetCurrentBackBufferIndex();
	// �P�D���\�[�X�o���A�ŏ������݉\�ɕύX
	barrierDesc.Transition.pResource = newEngine->GetBackBuffers()[bbIndex]; // �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ�
	newEngine->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//--------------------------- �`���w��R�}���h ---------------------------//
	// �Q�D�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	rtvHandle = newEngine->GetRTVHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * newEngine->GetDevice()->GetDescriptorHandleIncrementSize(
		newEngine->GetRTVHeapDesc().Type);
	newEngine->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	//--------------------------- ��ʃN���A�R�}���h ---------------------------//
	// �R�D��ʃN���A R G B A
	newEngine->GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	// �r���[�|�[�g�̏���
	viewport->Update();

	// �V�U�[��`�̏���
	scissorRectangle->Update();

	//---------- �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h ----------//
	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	newEngine->GetCommandList()->SetPipelineState(
		graphicsPipeline->GetPipelineState());
	newEngine->GetCommandList()->SetGraphicsRootSignature(
		graphicsPipeline->GetRootSignature());
}


void GraphicsCommand::PostUpdate()
{
	//---------------------- ���\�[�X�o���A�̕��A�R�}���h ----------------------//
	// �T�D���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ�
	newEngine->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//-------------------------- �R�}���h�̃t���b�V�� --------------------------//
	// ���߂̃N���[�Y
	result = newEngine->GetCommandList()->Close();
	assert(SUCCEEDED(result));
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { newEngine->GetCommandList() };
	newEngine->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v�i���\�̓��ւ��j
	result = newEngine->GetSwapChain()->Present(1, 0);
	assert(SUCCEEDED(result));

	//---------------------------- �R�}���h�����҂� ----------------------------//
	// �R�}���h�̎��s������҂�
	newEngine->GetCommandQueue()->Signal(newEngine->GetFence(), newEngine->PreIncreFenceVal());
	if (newEngine->GetFence()->GetCompletedValue() != newEngine->GetFenceVal())
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		newEngine->GetFence()->SetEventOnCompletion(newEngine->GetFenceVal(), event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// �L���[���N���A
	result = newEngine->GetCommandAllocataor()->Reset();
	assert(SUCCEEDED(result));
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	result = newEngine->GetCommandList()->Reset(newEngine->GetCommandAllocataor(), nullptr);
	assert(SUCCEEDED(result));
}

void GraphicsCommand::SetBackgroundColor(int Red, int Green, int Blue)
{
	clearColor[0] = Red / 255;
	clearColor[1] = Green / 255;
	clearColor[2] = Blue / 255;
}