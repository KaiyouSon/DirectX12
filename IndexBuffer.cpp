#include "IndexBuffer.h"
#include "NewEngineBase.h"
#include <cassert>

void IndexBuffer::Initialize(uint16_t indices[], const int& arrarySize)
{
	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * arrarySize);

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// インデックスバッファの生成
	ID3D12Resource* indexBuff = nullptr;
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&heapProp, // ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&resDesc, // リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&indexBuff));
	assert(SUCCEEDED(result));

	//------------------- インデックスバッファへのデータ転送 -------------------//
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	assert(SUCCEEDED(result));
	// 全頂点に対して
	for (int i = 0; i < arrarySize; i++)
	{
		indexMap[i] = indices[i]; // 座標をコピー
	}
	// 繋がりを解除
	indexBuff->Unmap(0, nullptr);

	// インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

D3D12_INDEX_BUFFER_VIEW* IndexBuffer::GetibViewAddress()
{
	return &ibView;
}
