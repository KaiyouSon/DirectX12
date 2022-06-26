#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <wrl.h>

class RenderBase
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr <T>;
private:
	HRESULT result;
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<ComPtr<ID3D12Resource>> backBuffers; // バックバッファ

	// デスクリプタヒープ
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	// フェンス
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	// ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter;

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
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<IDXGISwapChain4> GetSwapChain();
	ComPtr<ID3D12CommandAllocator> GetCommandAllocataor();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12CommandQueue> GetCommandQueue();
	ComPtr<ID3D12DescriptorHeap> GetRtvHeap();
	std::vector<ComPtr<ID3D12Resource>> GetBackBuffers();
	D3D12_DESCRIPTOR_HEAP_DESC GetRTVHeapDesc();
	ComPtr<ID3D12Fence> GetFence();
	UINT64 GetFenceVal();
	UINT64 PreIncreFenceVal();

	static RenderBase* GetInstance();
	static void DestroyInstance();
private:
	RenderBase() = default;
	~RenderBase() = default;

	RenderBase(const RenderBase&) = delete;
	RenderBase& operator=(const RenderBase&) = delete;
	RenderBase(const RenderBase&&) = delete;
	RenderBase& operator=(const RenderBase&&) = delete;
};

