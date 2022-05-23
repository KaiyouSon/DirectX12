#include "DepthBuffer.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include <cassert>

using namespace Microsoft::WRL;

void DepthBuffer::Initialize()
{
	// ���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();		// ��
	depthResourceDesc.Height = NewEngineWindow::GetInstance().GetWinHeight(); // ����
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�f�t�H���g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// �[�x�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// �[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;	// �[�x�l1.0f(�ő�l)�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g

	HRESULT result;

	// ���\�[�X�̐���
	ID3D12Resource* depthBuff = nullptr;
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, // �[�x�l�������݂Ɏg�p
			&depthClearValue,
			IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	// �[�x�r���[�p�f�X�N���v�^�q�[�v�̍쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	// �[�x�r���[�͈��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	// �[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	NewEngineBase::GetInstance().GetDevice()->
		CreateDepthStencilView(
			depthBuff,
			&dsvDesc,
			dsvHeap->GetCPUDescriptorHandleForHeapStart());

}

ComPtr<ID3D12DescriptorHeap> DepthBuffer::GetDsvHeap()
{
	return dsvHeap;
}

DepthBuffer& DepthBuffer::GetInstance()
{
	static DepthBuffer depthBuffer;
	return depthBuffer;
}