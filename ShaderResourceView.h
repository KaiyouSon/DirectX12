#pragma once
#include "Square.h"
#include "Cube.h"
#include <d3d12.h>
#include <vector>
#include <wrl.h>

class ShaderResourceView
{
private:
	// SRVヒープの先頭ハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	// SRV設定構造体
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	// srvCpuHandleのポインタを格納する変数
	std::vector <D3D12_CPU_DESCRIPTOR_HANDLE> srvCpuHandlePtr;

	UINT incrementIndex = 0;

private:

public:
	void Initialize();
	void CreatSrv(Square& square);
	void CreatSrv(Cube& cube);

public:

	// SRV用デスクリプタヒープを取得する関数
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetSrvHeap();

	D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGpuHandle();

	static ShaderResourceView* GetInstance();
	static void DestroyInstance();
private:
	ShaderResourceView() = default;
	~ShaderResourceView() = default;

	ShaderResourceView(const ShaderResourceView&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&) = delete;
	ShaderResourceView(const ShaderResourceView&&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&&) = delete;
};