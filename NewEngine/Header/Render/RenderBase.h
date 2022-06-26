#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <wrl.h>
#include "Header/TextureBuffer.h"

class RenderBase
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr <T>;
private:
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;

	// コマンド関連
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	// スワップチェーン
	ComPtr<IDXGISwapChain4> swapChain;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};		 // rtv設定構造体
	ComPtr<ID3D12DescriptorHeap> rtvDescHeap;		 // rtv用デスクリプタヒープ
	std::vector<ComPtr<ID3D12Resource>> backBuffers; // バックバッファ

	// フェンス
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	// 深度バッファ
	ComPtr<ID3D12DescriptorHeap> dsvDescHeap;	// 深度バッファビュー用デスクリプタヒープ
	ComPtr<ID3D12Resource> depthBuffer;			// 深度バッファ

	// srv
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// srv設定構造体
	ComPtr<ID3D12DescriptorHeap> srvDescHeap;	// srv用デスクリプタヒープ
	UINT incrementIndex = 1;

	// シェーダコンパイラー
	ComPtr <ID3DBlob> vsBlob;		// 頂点シェーダオブジェクト
	ComPtr <ID3DBlob> ps3DBlob;		// ピクセルシェーダオブジェクト
	ComPtr <ID3DBlob> ps2DBlob;		// ピクセルシェーダオブジェクト
	ComPtr <ID3DBlob> errorBlob;	// エラーオブジェクト
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];		// 頂点レイアウト

public:
	void Initialize();
	void CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc);

private:
	void DeviceInit();
	void CommandInit();
	void SwapChainInit();
	void FenceInit();
	void DepthBufferInit();
	void SrvInit();
	void ShaderCompilerInit();
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
	ComPtr<ID3D12DescriptorHeap> GetSrvDescHeap();

	ComPtr<ID3DBlob> GetvsBlob();		 // 頂点シェーダオブジェクトを取得する関数
	ComPtr<ID3DBlob> Getps3DBlob();		 // ピクセルシェーダオブジェクトを取得する関数
	ComPtr<ID3DBlob> Getps2DBlob();		 // ピクセルシェーダオブジェクトを取得する関数
	ComPtr<ID3DBlob> GeterrorBlob();	 // エラーオブジェクトを取得する関数
	D3D12_INPUT_ELEMENT_DESC* GetInputLayout();		// 頂点レイアウトを取得する関数
	int GetInputLayoutSize();						// 頂点レイアウトの要素数を取得する関数

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

