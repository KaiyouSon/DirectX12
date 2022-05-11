#include "ShaderResourceView.h"
#include "NewEngineBase.h"
#include "Square.h"
#include "Image.h"

#include <cassert>

extern NewEngineBase* newEngine;
extern Square* square;
extern Image* image;

void ShaderResourceView::Initialize()
{
	// SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// �V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	HRESULT result;

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = newEngine->GetDevice()->CreateDescriptorHeap(
		&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	// SRV�q�[�v�̐擪�n���h�����擾
	srvCpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	// �V�F�[�_�[���\�[�X�r���[�ݒ�
	//srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // RGBA float
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	//srvDesc.Texture2D.MipLevels = 1;

	srvDesc.Format = square->GetVertexBuffer()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = square->GetVertexBuffer()->resDesc.MipLevels;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	newEngine->GetDevice()->CreateShaderResourceView(
		square->GetTextureBuffer()->GetTextureBuff(), &srvDesc, srvCpuHandle);

	UINT descriptorSize = newEngine->GetDevice()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	srvCpuHandle.ptr += descriptorSize * 1;
	srvGpuHandle.ptr += descriptorSize * 1;

	srvDesc.Format = image->GetVertexBuffer()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = image->GetVertexBuffer()->resDesc.MipLevels;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	newEngine->GetDevice()->CreateShaderResourceView(
		image->GetTextureBuffer()->GetTextureBuff(), &srvDesc, srvCpuHandle);
}

ID3D12DescriptorHeap* ShaderResourceView::GetsrvHeap()
{
	return srvHeap;
}

ID3D12DescriptorHeap** ShaderResourceView::GetsrvHeapAddress()
{
	return &srvHeap;
}

D3D12_GPU_DESCRIPTOR_HANDLE ShaderResourceView::GetSrvGpuHandle()
{
	return srvGpuHandle;
}
