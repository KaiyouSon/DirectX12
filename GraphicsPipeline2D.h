#pragma once
#include <d3d12.h>
#include <wrl.h>

class GraphicsPipeline2D
{
private:
	// パイプランステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

public:
	void Initialize();
public:
	// パイプランステートを取得する関数
	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState();

	static GraphicsPipeline2D& GetInstance();
private:
	GraphicsPipeline2D() = default;
	~GraphicsPipeline2D() = default;

	GraphicsPipeline2D(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D(const GraphicsPipeline2D&&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&&) = delete;
};