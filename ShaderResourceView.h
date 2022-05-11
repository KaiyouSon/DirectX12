#pragma once
#include <d3d12.h>

class ShaderResourceView
{
private:
	// SRVヒープの先頭ハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// SRV用デスクリプタヒープ
	ID3D12DescriptorHeap* srvHeap;
	// SRV設定構造体
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

public:
	void Initialize();
public:

	// SRV用デスクリプタヒープを取得する関数
	ID3D12DescriptorHeap* GetsrvHeap();

	// SRV用デスクリプタヒープのアドレスを取得する関数
	ID3D12DescriptorHeap** GetsrvHeapAddress();

	D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGpuHandle();
};