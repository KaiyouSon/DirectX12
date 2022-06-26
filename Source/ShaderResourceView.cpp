#include "Header/ShaderResourceView.h"
#include "NewEngine/Header/Render/NewEngineBase.h"
#include <cassert>
using namespace Microsoft::WRL;

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
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));
}

void ShaderResourceView::CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc)
{
	// SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT descriptorSize = NewEngineBase::GetInstance()->GetDevice()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	srvCpuHandle.ptr += descriptorSize * incrementIndex;
	srvGpuHandle.ptr += descriptorSize * incrementIndex;

	texture.SetCpuHandle(srvCpuHandle);
	texture.SetGpuHandle(srvGpuHandle);

	// �V�F�[�_�[���\�[�X�r���[�ݒ�
	srvDesc.Format = textureResourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = textureResourceDesc.MipLevels;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	NewEngineBase::GetInstance()->GetDevice()->
		CreateShaderResourceView(texture.buffer.Get(), &srvDesc, srvCpuHandle);

	incrementIndex++;
}

ComPtr<ID3D12DescriptorHeap> ShaderResourceView::GetSrvHeap()
{
	return srvHeap;
}

ShaderResourceView* ShaderResourceView::GetInstance()
{
	static ShaderResourceView* shaderResourceView = new  ShaderResourceView;
	return shaderResourceView;
}

void ShaderResourceView::DestroyInstance()
{
	delete ShaderResourceView::GetInstance();
}
