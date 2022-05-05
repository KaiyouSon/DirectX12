#pragma once
#include <d3d12.h>

class GraphicsPipeline
{
private:
	// パイプランステート
	ID3D12PipelineState* pipelineState;
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
public:
	void Initialize();
public:
	ID3D12PipelineState* GetPipelineState();	// パイプランステートを取得する関数
	ID3D12RootSignature* GetRootSignature();	// ルートシグネチャを取得する関数
};
