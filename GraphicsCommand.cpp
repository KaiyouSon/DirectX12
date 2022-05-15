#include "GraphicsCommand.h"
#include "NewEngineBase.h"
#include "GraphicsPipeline.h"
#include "Viewport.h"
#include "ScissorRectangle.h"
#include "DepthBuffer.h"
#include <cassert>

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
	UINT bbIndex = NewEngineBase::GetInstance().GetSwapChain()->GetCurrentBackBufferIndex();
	// �P�D���\�[�X�o���A�ŏ������݉\�ɕύX
	barrierDesc.Transition.pResource =
		NewEngineBase::GetInstance().GetBackBuffers()[bbIndex]; // �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ�
	NewEngineBase::GetInstance().GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//--------------------------- �`���w��R�}���h ---------------------------//
	// �Q�D�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	rtvHandle = NewEngineBase::GetInstance().
		GetRTVHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * NewEngineBase::GetInstance().GetDevice()->
		GetDescriptorHandleIncrementSize(
			NewEngineBase::GetInstance().GetRTVHeapDesc().Type);
	
	// �[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle =DepthBuffer::GetInstance().
		GetDsvHeap()->GetCPUDescriptorHandleForHeapStart();
	NewEngineBase::GetInstance().GetCommandList()->
		OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// ��ʃN���A R G B A
	NewEngineBase::GetInstance().GetCommandList()->
		ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	// �[�x�o�b�t�@�N���A
	NewEngineBase::GetInstance().GetCommandList()->
		ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// �r���[�|�[�g�̏���
	viewport->Update();

	// �V�U�[��`�̏���
	scissorRectangle->Update();

	//---------- �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h ----------//
	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		SetPipelineState(graphicsPipeline->GetPipelineState());
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootSignature(graphicsPipeline->GetRootSignature());
}


void GraphicsCommand::PostUpdate()
{
	//---------------------- ���\�[�X�o���A�̕��A�R�}���h ----------------------//
	// �T�D���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ�
	NewEngineBase::GetInstance().GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//-------------------------- �R�}���h�̃t���b�V�� --------------------------//
	// ���߂̃N���[�Y
	result = NewEngineBase::GetInstance().GetCommandList()->Close();
	assert(SUCCEEDED(result));
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { NewEngineBase::GetInstance().GetCommandList() };
	NewEngineBase::GetInstance().GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v�i���\�̓��ւ��j
	result = NewEngineBase::GetInstance().GetSwapChain()->Present(1, 0);
	assert(SUCCEEDED(result));

	//---------------------------- �R�}���h�����҂� ----------------------------//
	// �R�}���h�̎��s������҂�
	NewEngineBase::GetInstance().GetCommandQueue()->Signal(
		NewEngineBase::GetInstance().GetFence(), NewEngineBase::GetInstance().PreIncreFenceVal());
	if (NewEngineBase::GetInstance().GetFence()->GetCompletedValue() !=
		NewEngineBase::GetInstance().GetFenceVal())
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		NewEngineBase::GetInstance().GetFence()->SetEventOnCompletion(
			NewEngineBase::GetInstance().GetFenceVal(), event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// �L���[���N���A
	result = NewEngineBase::GetInstance().GetCommandAllocataor()->Reset();
	assert(SUCCEEDED(result));
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	result = NewEngineBase::GetInstance().GetCommandList()->
		Reset(NewEngineBase::GetInstance().GetCommandAllocataor(), nullptr);
	assert(SUCCEEDED(result));
}

void GraphicsCommand::SetBackgroundColor(float Red, float Green, float Blue)
{
	clearColor[0] = Red / 255;
	clearColor[1] = Green / 255;
	clearColor[2] = Blue / 255;
}