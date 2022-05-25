#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include <cassert>
#include <string>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
using namespace Microsoft::WRL;

void NewEngineBase::Initialize()
{
	AdapterInit();

	DeviceInit();

	CommandListInit();

	CommandQueueInit();

	SwapChainInit();

	DescriptorHeapInit();

	BackBufferInit();

	RenderTargetViewInit();

	FenceInit();
}

void NewEngineBase::AdapterInit()
{
	// DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// �A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;

	// �p�t�H�[�}���X���������̂��珇�ɁA�S�ẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		// ���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}

	// �Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);
		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i].Get();
			break;
		}
	}
}
void NewEngineBase::DeviceInit()
{
	//----------------------------- �f�o�C�X�̐��� -----------------------------//
	// �Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;
	for (size_t i = 0; i < _countof(levels); i++)
	{
		// �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(device.GetAddressOf()));
		if (result == S_OK) {
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}
}
void NewEngineBase::CommandListInit()
{
	// �R�}���h�A���P�[�^�𐶐�
	result = device.Get()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));
	assert(SUCCEEDED(result));
	// �R�}���h���X�g�𐶐�
	result = device.Get()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));
}
void NewEngineBase::CommandQueueInit()
{
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�R�}���h�L���[�𐶐�
	result = device.Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
void NewEngineBase::SwapChainInit()
{
	//------------------------- �X���b�v�`�F�[���̐��� -------------------------//
	// �X���b�v�`�F�[���̐ݒ�
	swapChainDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();
	swapChainDesc.Height = NewEngineWindow::GetInstance().GetWinHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �F���̏���
	swapChainDesc.SampleDesc.Count = 1; // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2; // �o�b�t�@�����Q�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// �X���b�v�`�F�[���̐���
	ComPtr<IDXGISwapChain1> swapChain1;
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(), NewEngineWindow::GetInstance().GetHwnd(), &swapChainDesc, nullptr, nullptr,
		&swapChain1);
	swapChain1.As(&swapChain);
	assert(SUCCEEDED(result));
}
void NewEngineBase::DescriptorHeapInit()
{
	// �f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // ���\�̂Q��
	// �f�X�N���v�^�q�[�v�̐���
	device.Get()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
}
void NewEngineBase::BackBufferInit()
{
	//----------------------------- �o�b�N�o�b�t�@ -----------------------------//
	// �o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);
}
void NewEngineBase::RenderTargetViewInit()
{
	//------------------ �����_�[�^�[�Q�b�g�r���[(RTV)�̐��� -------------------//
	for (size_t i = 0; i < backBuffers.size(); i++)
		// �X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	{
		// �X���b�v�`�F�[������o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// �f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		// �����\���ŃA�h���X�������
		rtvHandle.ptr += i * device.Get()->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[�̐���
		device.Get()->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}
void NewEngineBase::FenceInit()
{
	// �t�F���X�̐���
	result = device.Get()->CreateFence(
		fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
}

#pragma region // ------------------------- �Q�b�^�[�֘A ------------------------- //
ComPtr<ID3D12Device> NewEngineBase::GetDevice()
{
	return device;
}
ComPtr<IDXGISwapChain4> NewEngineBase::GetSwapChain()
{
	return swapChain;
}
ComPtr<ID3D12CommandAllocator> NewEngineBase::GetCommandAllocataor()
{
	return cmdAllocator;
}
ComPtr<ID3D12GraphicsCommandList> NewEngineBase::GetCommandList()
{
	return commandList;
}
ComPtr<ID3D12CommandQueue> NewEngineBase::GetCommandQueue()
{
	return commandQueue;
}
ComPtr<ID3D12DescriptorHeap> NewEngineBase::GetRtvHeap()
{
	return rtvHeap;
}
D3D12_DESCRIPTOR_HEAP_DESC NewEngineBase::GetRTVHeapDesc()
{
	return rtvHeapDesc;
}
ComPtr<ID3D12Fence> NewEngineBase::GetFence()
{
	return fence;
}
UINT64 NewEngineBase::GetFenceVal()
{
	return fenceVal;
}
UINT64 NewEngineBase::PreIncreFenceVal()
{
	++fenceVal;
	return fenceVal;
}
std::vector<ComPtr<ID3D12Resource>> NewEngineBase::GetBackBuffers()
{
	return backBuffers;
}
NewEngineBase* NewEngineBase::GetInstance()
{
	static NewEngineBase* newEngineBase = new NewEngineBase;
	return newEngineBase;
}
void NewEngineBase::DestroyInstance()
{
	delete NewEngineBase::GetInstance();
}
#pragma endregion