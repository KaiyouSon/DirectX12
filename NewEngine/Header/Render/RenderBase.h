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
	// デバイス関連
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;

	// コマンド関連
	ComPtr<ID3D12CommandAllocator> commandAllocator;
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

	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;

	// グラフィックスパイプライン関連
	ComPtr <ID3D12PipelineState> pipelineState3D;
	ComPtr <ID3D12PipelineState> pipelineState2D;

	// 描画処理関連
	D3D12_RESOURCE_BARRIER barrierDesc{};	// リソースバリア
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;	// レンダーターゲットビューのハンドル
	float clearColor[4];	// 画面色

public:
	void Initialize();
	void PreDraw();
	void Draw3D();
	void Draw2D();
	void PostDraw();
	void CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc);

private:
	// 初期化関連
	void DeviceInit();
	void CommandInit();
	void SwapChainInit();
	void FenceInit();
	void DepthBufferInit();
	void SrvInit();
	void ShaderCompilerInit();
	void RootSignatureInit();
	void GraphicsPipelineInit();

public:
	ComPtr<ID3D12Device> GetDevice();
	ComPtr<IDXGISwapChain4> GetSwapChain();
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

	ComPtr<ID3D12RootSignature> GetRootSignature();		// ルートシグネチャを取得する関数

	ComPtr <ID3D12PipelineState> GetPipelineState3D();	// 3D用パイプラインステートを取得する関数
	ComPtr <ID3D12PipelineState> GetPipelineState2D();	// 2D用パイプラインステートを取得する関数
	
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

