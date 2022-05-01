#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

class NewEngineBase
{
private:
	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;

	// バックバッファ
	std::vector<ID3D12Resource*> backBuffers;

	// デスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	// フェンス
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;

	// ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter = nullptr;

	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

public:
	void Initialize();

private:
	void AdapterInit();
	void DeviceInit();
	void CommandListInit();
	void CommandQueueInit();
	void SwapChainInit();
	void DescriptorHeapInit();
	void BackBufferInit();
	void RenderTargetViewInit();
	void FenceInit();

public:
	ID3D12Device* GetDevice();
	IDXGISwapChain4* GetSwapChain();
	ID3D12GraphicsCommandList* GetCommandList();
	ID3D12DescriptorHeap* GetRTVHeap();
	ID3D12CommandQueue* GetCommandQueue();
	ID3D12CommandAllocator* GetCommandAllocataor();

	std::vector<ID3D12Resource*> GetBackBuffers();
	D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc();
	ID3D12Fence* GetFence();
	UINT64 GetFenceVal();
	UINT64 PreIncreFenceVal();
};

