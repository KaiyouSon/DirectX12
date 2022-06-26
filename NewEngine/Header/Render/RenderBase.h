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

	// コマンド関連
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	// スワップチェーン
	ComPtr<IDXGISwapChain4> swapChain;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};		 // 設定用デスクリプタヒープ構造体
	ComPtr<ID3D12DescriptorHeap> rtvDescHeap;		 // レンダーターゲットビュー用デスクリプタヒープ
	std::vector<ComPtr<ID3D12Resource>> backBuffers; // バックバッファ

	// フェンス
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescHeap;	// 深度バッファビュー用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;			// 深度バッファ

public:
	void Initialize();

private:
	void DeviceInit();
	void CommandInit();
	void SwapChainInit();
	void FenceInit();
	void DepthBufferInit();

public:
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<IDXGISwapChain4> GetSwapChain();
	ComPtr<ID3D12CommandAllocator> GetCommandAllocataor();
	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12CommandQueue> GetCommandQueue();
	ComPtr<ID3D12DescriptorHeap> GetRtvHeap();
	std::vector<ComPtr<ID3D12Resource>> GetBackBuffers();
	D3D12_DESCRIPTOR_HEAP_DESC GetRtvDescHeap();
	ComPtr<ID3D12Fence> GetFence();
	UINT64 GetFenceVal();
	UINT64 PreIncreFenceVal();

	ComPtr<ID3D12DescriptorHeap> GetDsvDescHeap();

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

