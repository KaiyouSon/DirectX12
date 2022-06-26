#include "Header/GraphicsCommand.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "Header/GraphicsPipeline2D.h"
#include "Header/GraphicsPipeline3D.h"
#include "Header/RootSignature.h"
#include <cassert>

void GraphicsCommand::PreDraw()
{
	//---------------------- ���\�[�X�o���A�̕ύX�R�}���h ----------------------//
	// �o�b�N�o�b�t�@�̔ԍ����擾�i2�Ȃ̂�0�Ԃ�1�ԁj
	UINT bbIndex = RenderBase::GetInstance()->GetSwapChain()->GetCurrentBackBufferIndex();
	// �P�D���\�[�X�o���A�ŏ������݉\�ɕύX
	barrierDesc.Transition.pResource =
		RenderBase::GetInstance()->GetBackBuffers()[bbIndex].Get();	// �o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;	// �\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ�
	RenderBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//--------------------------- �`���w��R�}���h ---------------------------//
	// �Q�D�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	rtvHandle = RenderBase::GetInstance()->
		GetRtvHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * RenderBase::GetInstance()->GetDevice()->
		GetDescriptorHandleIncrementSize(RenderBase::GetInstance()->GetRtvDescHeap().Type);

	// �[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = RenderBase::GetInstance()->
		GetDsvDescHeap()->GetCPUDescriptorHandleForHeapStart();
	RenderBase::GetInstance()->GetCommandList()->
		OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// ��ʃN���A R G B A
	RenderBase::GetInstance()->GetCommandList()->
		ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	// �[�x�o�b�t�@�N���A
	RenderBase::GetInstance()->GetCommandList()->
		ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// ���[�g�V�O�l�`���̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootSignature(RootSignature::GetInstance()->GetRootSignature().Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
}
void GraphicsCommand::Draw3D()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h( 3D�� )
	RenderBase::GetInstance()->GetCommandList()->
		SetPipelineState(GraphicsPipeline3D::GetInstance()->GetPipelineState().Get());
}
void GraphicsCommand::Draw2D()
{
	// �p�C�v���C���X�e�[�g�̐ݒ�R�}���h( 2D�� )
	RenderBase::GetInstance()->GetCommandList()->
		SetPipelineState(GraphicsPipeline2D::GetInstance()->GetPipelineState().Get());
}
void GraphicsCommand::PostDraw()
{
	//---------------------- ���\�[�X�o���A�̕��A�R�}���h ----------------------//
	// �T�D���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ�
	RenderBase::GetInstance()->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//-------------------------- �R�}���h�̃t���b�V�� --------------------------//
	// ���߂̃N���[�Y
	result = RenderBase::GetInstance()->GetCommandList()->Close();
	assert(SUCCEEDED(result));
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] =
	{ RenderBase::GetInstance()->GetCommandList().Get() };
	RenderBase::GetInstance()->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v�i���\�̓��ւ��j
	result = RenderBase::GetInstance()->GetSwapChain()->Present(1, 0);
	assert(SUCCEEDED(result));

	// �R�}���h�̎��s������҂�
	RenderBase::GetInstance()->GetCommandQueue()->Signal(
		RenderBase::GetInstance()->GetFence().Get(),
		RenderBase::GetInstance()->PreIncreFenceVal());
	if (RenderBase::GetInstance()->GetFence().Get()->GetCompletedValue() !=
		RenderBase::GetInstance()->GetFenceVal())
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		RenderBase::GetInstance()->GetFence().Get()->SetEventOnCompletion(
			RenderBase::GetInstance()->GetFenceVal(), event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// �L���[���N���A
	result = RenderBase::GetInstance()->GetCommandAllocataor()->Reset();
	assert(SUCCEEDED(result));
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	result = RenderBase::GetInstance()->GetCommandList().Get()->
		Reset(RenderBase::GetInstance()->GetCommandAllocataor().Get(), nullptr);
	assert(SUCCEEDED(result));
}

void GraphicsCommand::SetBackgroundColor(float Red, float Green, float Blue)
{
	clearColor[0] = Red / 255;
	clearColor[1] = Green / 255;
	clearColor[2] = Blue / 255;
}

GraphicsCommand& GraphicsCommand::GetInstance()
{
	static GraphicsCommand graphicsCommand;
	return graphicsCommand;

	
}