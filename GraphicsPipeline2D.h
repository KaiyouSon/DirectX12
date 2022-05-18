#pragma once
#include <d3d12.h>

class GraphicsPipeline2D
{
private:
	// パイプランステート
	ID3D12PipelineState* pipelineState;

public:
	void Initialize();
public:
	ID3D12PipelineState* GetPipelineState();	// パイプランステートを取得する関数

	static GraphicsPipeline2D& GetInstance();
private:
	GraphicsPipeline2D() = default;
	~GraphicsPipeline2D() = default;

	GraphicsPipeline2D(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&) = delete;
	GraphicsPipeline2D(const GraphicsPipeline2D&&) = delete;
	GraphicsPipeline2D& operator=(const GraphicsPipeline2D&&) = delete;
};