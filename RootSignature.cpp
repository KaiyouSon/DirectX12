#include "RootSignature.h"
#include "ShaderCompiler.h"
#include "NewEngineBase.h"

#include <cassert>

void RootSignature::Initialize()
{
	// �f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1;			// ��x�̕`��Ɏg���e�N�X�`����1���Ȃ̂łP
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;		// �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// ���J��Ԃ�(�^�C�����O)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// �c�J��Ԃ�(�^�C�����O)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// ���s�J��Ԃ�(�^�C�����O)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;	// �{�[�_�[�̎��͍�
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;					// �S�Ẵ��j�A���
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;									// �~�b�v�}�b�v�ő�l
	samplerDesc.MinLOD = 0.0f;												// �~�b�v�}�b�v�ŏ��l
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;			// �s�N�Z���V�F�[�_����̂ݎg�p�\

	// ���[�g�p�����[�^�[�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	// �萔�o�b�t�@��0��
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	// ���
	rootParams[0].Descriptor.ShaderRegister = 0;					// �萔�o�b�t�@�ԍ�
	rootParams[0].Descriptor.RegisterSpace = 0;						// �f�t�H���g�l
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	// �S�ẴV�F�[�_���猩����
	// �e�N�X�`�����W�X�^0��
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // ���
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;		  // �f�X�N���v�^�����W
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;					  // �f�X�N���v�^�����W��
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;			  // �S�ẴV�F�[�_���猩����
	// �萔�o�b�t�@��1��
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	// ���
	rootParams[2].Descriptor.ShaderRegister = 1;					// �萔�o�b�t�@�ԍ�
	rootParams[2].Descriptor.RegisterSpace = 0;						// �f�t�H���g�l
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	// �S�ẴV�F�[�_���猩����

	HRESULT result;

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;	// ���[�g�p�����[�^�̐擪�A�h���X
	rootSignatureDesc.NumParameters = _countof(rootParams);		// ���[�g�p�����[�^��
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(
		&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob,
		ShaderCompiler::GetInstance().GeterrorBlobAddress());
	assert(SUCCEEDED(result));
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateRootSignature(
			0,
			rootSigBlob->GetBufferPointer(),
			rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
}

ID3D12RootSignature* RootSignature::GetRootSignature()
{
	return rootSignature;
}

RootSignature& RootSignature::GetInstance()
{
	static RootSignature rootSignature;
	return rootSignature;
}
