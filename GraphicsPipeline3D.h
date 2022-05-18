#pragma once
#include <d3d12.h>

class GraphicsPipeline3D
{
private:
	// �p�C�v�����X�e�[�g
	ID3D12PipelineState* pipelineState;

public:
	void Initialize();
public:
	ID3D12PipelineState* GetPipelineState();	// �p�C�v�����X�e�[�g���擾����֐�

	static GraphicsPipeline3D& GetInstance();
private:
	GraphicsPipeline3D() = default;
	~GraphicsPipeline3D() = default;

	GraphicsPipeline3D(const GraphicsPipeline3D&) = delete;
	GraphicsPipeline3D& operator=(const GraphicsPipeline3D&) = delete;
	GraphicsPipeline3D(const GraphicsPipeline3D&&) = delete;
	GraphicsPipeline3D& operator=(const GraphicsPipeline3D&&) = delete;
};
