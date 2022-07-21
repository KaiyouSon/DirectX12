#pragma once
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <wrl.h>

class RenderBase
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr <T>;
	static float clearColor[4];

public:
	void Initialize();
	void PreDraw();
	void SetDraw3D();
	void SetDraw2D();
	void SetDrawLine();
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
	ComPtr<ID3D12Device> GetDevice() const;
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12DescriptorHeap> GetSrvDescHeap() const;

	ComPtr <ID3D12RootSignature> GetRootSignature() const;
	ComPtr <ID3D12PipelineState> GetPipelineStateAlpha3D() const;
	ComPtr <ID3D12PipelineState> GetPipelineStateAdd3D() const;
	ComPtr <ID3D12PipelineState> GetPipelineStateAlpha2D() const;
	ComPtr <ID3D12PipelineState> GetPipelineStateLine() const;
	ComPtr <ID3D12PipelineState> GetPipelineStateAlphaRenderTexture() const;

	static RenderBase* GetInstance();
	static void DestroyInstance();
private:
	RenderBase() = default;
	~RenderBase() = default;

	RenderBase(const RenderBase&) = delete;
	RenderBase& operator=(const RenderBase&) = delete;
	RenderBase(const RenderBase&&) = delete;
	RenderBase& operator=(const RenderBase&&) = delete;

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
	ComPtr<ID3D12DescriptorHeap> srvDescHeap;	// srv用デスクリプタヒープ
	UINT incrementIndex = 1;

	// シェーダコンパイラー
	ComPtr <ID3DBlob> vsBlob;		// 頂点シェーダオブジェクト
	ComPtr <ID3DBlob> ps3DBlob;		// ピクセルシェーダオブジェクト
	ComPtr <ID3DBlob> ps2DBlob;		// ピクセルシェーダオブジェクト
	ComPtr <ID3DBlob> errorBlob;	// エラーオブジェクト
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];		// 頂点レイアウト

	ComPtr <ID3DBlob> renderTextureVSBlob;
	ComPtr <ID3DBlob> renderTexturePSBlob;
	D3D12_INPUT_ELEMENT_DESC renderTextureInputLayout[2];

	// グラフィックスパイプライン関連
	ComPtr <ID3D12PipelineState> pipelineStateAlpha3D;
	ComPtr <ID3D12PipelineState> pipelineStateAdd3D;
	ComPtr <ID3D12PipelineState> pipelineStateAlpha2D;
	ComPtr <ID3D12PipelineState> pipelineStateLine;
	ComPtr <ID3D12PipelineState> pipelineStateAlphaRenderTexture;
	ComPtr <ID3D12RootSignature> rootSignature;

	// 描画処理関連
	D3D12_RESOURCE_BARRIER barrierDesc{};	// リソースバリア
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;	// レンダーターゲットビューのハンドル
};

extern RenderBase* renderBase;

