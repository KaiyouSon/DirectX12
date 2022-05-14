#include "ShaderResourceView.h"
#include "NewEngineBase.h"

#include <cassert>

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
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateDescriptorHeap(
			&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));
}

void ShaderResourceView::CreatSrv(Image& image)
{
	// SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE _srvCpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT descriptorSize = NewEngineBase::GetInstance().GetDevice()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	_srvCpuHandle.ptr += descriptorSize * incrementIndex;
	_srvGpuHandle.ptr += descriptorSize * incrementIndex;

	srvCpuHandle = _srvCpuHandle;
	srvGpuHandle = _srvGpuHandle;

	// シェーダーリソースビュー設定
	srvDesc.Format = image.GetVertexBuffer()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = image.GetVertexBuffer()->resDesc.MipLevels;

	// ハンドルの指す位置にシェーダーリソースビュー作成
	NewEngineBase::GetInstance().GetDevice()->
		CreateShaderResourceView(
			image.GetTextureBuffer()->GetTextureBuff(), &srvDesc, _srvCpuHandle);

	image.SetGpuHandle(_srvGpuHandle);

	incrementIndex++;
}

ID3D12DescriptorHeap* ShaderResourceView::GetsrvHeap()
{
	return srvHeap;
}

ID3D12DescriptorHeap** ShaderResourceView::GetsrvHeapAddress()
{
	return &srvHeap;
}

D3D12_GPU_DESCRIPTOR_HANDLE ShaderResourceView::GetSrvGpuHandle()
{
	return srvGpuHandle;
}

ShaderResourceView& ShaderResourceView::GetInstance()
{
	static ShaderResourceView shaderResourceView;
	return shaderResourceView;
}
