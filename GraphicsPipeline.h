#pragma once
#include <d3d12.h>

class GraphicsPipeline
{
private:
	// �p�C�v�����X�e�[�g
	ID3D12PipelineState* pipelineState;
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
public:
	void Initialize();
public:
	ID3D12PipelineState* GetPipelineState();	// �p�C�v�����X�e�[�g���擾����֐�
	ID3D12RootSignature* GetRootSignature();	// ���[�g�V�O�l�`�����擾����֐�
};
