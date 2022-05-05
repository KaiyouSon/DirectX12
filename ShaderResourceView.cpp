#include "ShaderResourceView.h"
#include "NewEngineBase.h"
#include "TextureBuffer.h"
#include "VertexBuffer.h"
#include "Square.h"

#include <cassert>

extern NewEngineBase* newEngine;
extern Square* square;

void ShaderResourceView::Initialize()
{
	// SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// シェーダから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	HRESULT result;

	// 設定を元にSRV用デスクリプタヒープを生成
	result = newEngine->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	// SRVヒープの先頭ハンドルを取得
	srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	// シェーダーリソースビュー設定
	//srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // RGBA float
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	//srvDesc.Texture2D.MipLevels = 1;

	srvDesc.Format = square->GetVertexBuffer()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = square->GetVertexBuffer()->resDesc.MipLevels;

	// ハンドルの指す位置にシェーダーリソースビュー作成
	newEngine->GetDevice()->CreateShaderResourceView(
		square->GetTextureBuffer()->GetTextureBuff(), &srvDesc, srvHandle);
}

D3D12_CPU_DESCRIPTOR_HANDLE ShaderResourceView::GetsrvHandle()
{
	return srvHandle;
}

ID3D12DescriptorHeap* ShaderResourceView::GetsrvHeap()
{
	return srvHeap;
}

ID3D12DescriptorHeap** ShaderResourceView::GetsrvHeapAddress()
{
	return &srvHeap;
}

D3D12_SHADER_RESOURCE_VIEW_DESC* ShaderResourceView::GetsrvDescAddress()
{
	return &srvDesc;
}
