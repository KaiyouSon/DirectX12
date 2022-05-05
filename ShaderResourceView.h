#pragma once
#include <d3d12.h>

class ShaderResourceView
{
private:
	// SRVヒープの先頭ハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;
	// SRV用デスクリプタヒープ
	ID3D12DescriptorHeap* srvHeap;
	// SRV設定構造体
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
public:
	void Initialize();
public:
	// SRVヒープの先頭ハンドルを取得する関数
	D3D12_CPU_DESCRIPTOR_HANDLE GetsrvHandle();

	// SRV用デスクリプタヒープを取得する関数
	ID3D12DescriptorHeap* GetsrvHeap();

	// SRV用デスクリプタヒープのアドレスを取得する関数
	ID3D12DescriptorHeap** GetsrvHeapAddress();

	// SRV設定構造体のアドレスを取得する関数
	D3D12_SHADER_RESOURCE_VIEW_DESC* GetsrvDescAddress();
};