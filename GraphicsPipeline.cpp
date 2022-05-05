#include "GraphicsPipeline.h"
#include "ShaderCompiler.h"
#include "NewEngineBase.h"

#include <cassert>

extern ShaderCompiler* shaderCompiler;
extern NewEngineBase* newEngine;

void GraphicsPipeline::Initialize()
{
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = shaderCompiler->GetvsBlob()->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = shaderCompiler->GetvsBlob()->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = shaderCompiler->GetpsBlob()->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = shaderCompiler->GetpsBlob()->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask =
	//	D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��

	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendEnable = true;					// �u�����h��L���ɂ���
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	// ���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		// �\�[�X�̒l��100���g��
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	// �f�X�g�̒l��  0���g��

	// ���Z����
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	// ���Z
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;		// �\�[�X�̒l��100���g��
	//blenddesc.DestBlend = D3D12_BLEND_ONE;	// �f�X�g�̒l��100���g��

	// ���Z����
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;	// �f�X�g����\�[�X�����Z
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;				// �\�[�X�̒l��100���g��
	//blenddesc.DestBlend = D3D12_BLEND_ONE;			// �f�X�g�̒l��100���g��

	// �F���]
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;		// 1.0f-�f�X�g�J���[�̒l
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;				// �g��Ȃ�

	// ����������
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// ���Z
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			// �\�[�X�̃A���t�@�l
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	// 1.0f-�\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = shaderCompiler->GetInputLayout();
	pipelineDesc.InputLayout.NumElements = shaderCompiler->GetInputLayoutSize();

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	//---------------------------------------------------------------------------------------//

	// �f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1;			// ��x�̕`��Ɏg���e�N�X�`����1���Ȃ̂łP
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;		// �e�N�X�`�����W�X�^0��
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

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
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, shaderCompiler->GeterrorBlobAddress());
	assert(SUCCEEDED(result));
	result = newEngine->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature;

	// �p�C�v�����X�e�[�g�̐���
	result = newEngine->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

ID3D12PipelineState* GraphicsPipeline::GetPipelineState()
{
	return pipelineState;
}

ID3D12RootSignature* GraphicsPipeline::GetRootSignature()
{
	return rootSignature;
}