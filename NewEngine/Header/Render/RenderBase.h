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
	// �������֘A
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
	// �f�o�C�X�֘A
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;

	// �R�}���h�֘A
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	// �X���b�v�`�F�[��
	ComPtr<IDXGISwapChain4> swapChain;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};		 // rtv�ݒ�\����
	ComPtr<ID3D12DescriptorHeap> rtvDescHeap;		 // rtv�p�f�X�N���v�^�q�[�v
	std::vector<ComPtr<ID3D12Resource>> backBuffers; // �o�b�N�o�b�t�@

	// �t�F���X
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	// �[�x�o�b�t�@
	ComPtr<ID3D12DescriptorHeap> dsvDescHeap;	// �[�x�o�b�t�@�r���[�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12Resource> depthBuffer;			// �[�x�o�b�t�@

	// srv
	ComPtr<ID3D12DescriptorHeap> srvDescHeap;	// srv�p�f�X�N���v�^�q�[�v
	UINT incrementIndex = 1;

	// �V�F�[�_�R���p�C���[
	ComPtr <ID3DBlob> vsBlob;		// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> ps3DBlob;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> ps2DBlob;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> errorBlob;	// �G���[�I�u�W�F�N�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];		// ���_���C�A�E�g

	ComPtr <ID3DBlob> renderTextureVSBlob;
	ComPtr <ID3DBlob> renderTexturePSBlob;
	D3D12_INPUT_ELEMENT_DESC renderTextureInputLayout[2];

	// �O���t�B�b�N�X�p�C�v���C���֘A
	ComPtr <ID3D12PipelineState> pipelineStateAlpha3D;
	ComPtr <ID3D12PipelineState> pipelineStateAdd3D;
	ComPtr <ID3D12PipelineState> pipelineStateAlpha2D;
	ComPtr <ID3D12PipelineState> pipelineStateLine;
	ComPtr <ID3D12PipelineState> pipelineStateAlphaRenderTexture;
	ComPtr <ID3D12RootSignature> rootSignature;

	// �`�揈���֘A
	D3D12_RESOURCE_BARRIER barrierDesc{};	// ���\�[�X�o���A
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;	// �����_�[�^�[�Q�b�g�r���[�̃n���h��
};

extern RenderBase* renderBase;

