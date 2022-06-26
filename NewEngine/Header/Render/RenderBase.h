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
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// srv�ݒ�\����
	ComPtr<ID3D12DescriptorHeap> srvDescHeap;	// srv�p�f�X�N���v�^�q�[�v
	UINT incrementIndex = 1;

	// �V�F�[�_�R���p�C���[
	ComPtr <ID3DBlob> vsBlob;		// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> ps3DBlob;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> ps2DBlob;		// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr <ID3DBlob> errorBlob;	// �G���[�I�u�W�F�N�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];		// ���_���C�A�E�g

	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;

	// �O���t�B�b�N�X�p�C�v���C���֘A
	ComPtr <ID3D12PipelineState> pipelineState3D;
	ComPtr <ID3D12PipelineState> pipelineState2D;

	// �`�揈���֘A
	D3D12_RESOURCE_BARRIER barrierDesc{};	// ���\�[�X�o���A
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;	// �����_�[�^�[�Q�b�g�r���[�̃n���h��
	float clearColor[4];	// ��ʐF

public:
	void Initialize();
	void PreDraw();
	void Draw3D();
	void Draw2D();
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

	ComPtr<ID3D12RootSignature> GetRootSignature();		// ���[�g�V�O�l�`�����擾����֐�

	ComPtr <ID3D12PipelineState> GetPipelineState3D();	// 3D�p�p�C�v���C���X�e�[�g���擾����֐�
	ComPtr <ID3D12PipelineState> GetPipelineState2D();	// 2D�p�p�C�v���C���X�e�[�g���擾����֐�
	
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

