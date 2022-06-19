#include "Header/GraphicsPipeline3D.h"
#include "Header/ShaderCompiler.h"
#include "Header/NewEngineBase.h"
#include "Header/RootSignature.h"
#include <cassert>
using namespace Microsoft::WRL;

void GraphicsPipeline3D::Initialize()
{
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode =
		ShaderCompiler::GetInstance()->GetvsBlob()->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength =
		ShaderCompiler::GetInstance()->GetvsBlob()->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode =
		ShaderCompiler::GetInstance()->GetpsBlob()->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength =
		ShaderCompiler::GetInstance()->GetpsBlob()->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// �w�ʂ��J�����O
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipelineDesc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g���s��
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;	// �������݋���
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	// �������ق����̗p
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g

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
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;		// 1.0f-�\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs =
		ShaderCompiler::GetInstance()->GetInputLayout();
	pipelineDesc.InputLayout.NumElements =
		ShaderCompiler::GetInstance()->GetInputLayoutSize();

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = RootSignature::GetInstance()->GetRootSignature().Get();

	HRESULT result;

	// �p�C�v�����X�e�[�g�̐���
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

ComPtr<ID3D12PipelineState>GraphicsPipeline3D::GetPipelineState()
{
	return pipelineState;
}

GraphicsPipeline3D* GraphicsPipeline3D::GetInstance()
{
	static GraphicsPipeline3D* graphicsPipeline = new GraphicsPipeline3D;
	return graphicsPipeline;
}

void GraphicsPipeline3D::DestroyInstance()
{
	delete GraphicsPipeline3D::GetInstance();
}
