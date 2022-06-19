#pragma once
#include <d3d12.h>
#include <wrl.h>

class GraphicsPipeline3D
{
private:
	// �p�C�v�����X�e�[�g
	Microsoft::WRL::ComPtr <ID3D12PipelineState> pipelineState;

public:
	void Initialize();
public:
	// �p�C�v�����X�e�[�g���擾����֐�
	Microsoft::WRL::ComPtr <ID3D12PipelineState> GetPipelineState();

	static GraphicsPipeline3D* GetInstance();
	static void DestroyInstance();
private:
	GraphicsPipeline3D() = default;
	~GraphicsPipeline3D() = default;

	GraphicsPipeline3D(const GraphicsPipeline3D&) = delete;
	GraphicsPipeline3D& operator=(const GraphicsPipeline3D&) = delete;
	GraphicsPipeline3D(const GraphicsPipeline3D&&) = delete;
	GraphicsPipeline3D& operator=(const GraphicsPipeline3D&&) = delete;
};
