#pragma once
#include <d3d12.h>
#include "Vertex.h"

class VertexBuffer
{
private:
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
public:
	// リソース
	D3D12_RESOURCE_DESC resDesc{};
public:
	void Initialize(Vertex vertices[], int arrarySize);
public:
	// 頂点バッファビューを取得する関数
	D3D12_VERTEX_BUFFER_VIEW* GetvbViewAddress();
	// 頂点バッファにデータ転送する関数
	void TransferDateToVerBuff();	
};