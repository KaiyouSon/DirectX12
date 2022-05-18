#pragma once
#include <d3d12.h>

class GraphicsPipeline2D
{
private:
	// �p�C�v�����X�e�[�g
	ID3D12PipelineState* pipelineState;

public:
	void Initialize();
public:
	ID3D12PipelineState* GetPipelineState();	// �p�C�v�����X�e�[�g���擾����֐�

	static GraphicsPipeline2D& GetInstance();
private:
	GraphicsPipeline2D() = default;
	~GraphicsPipeline2D() = default;

	GraphicsPipeline2D(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D(const GraphicsPipeline2D&&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&&) = delete;
};