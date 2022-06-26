#include "NewEngine/Header/Render/RenderBase.h"
#include "Header/NewEngineWindow.h"
#include <cassert>
#include <string>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
using namespace Microsoft::WRL;

void RenderBase::Initialize()
{
	DeviceInit();			// �f�o�C�X�̏�����
	CommandInit();			// �R�}���h�֘A�̏�����
	SwapChainInit();		// �X���b�v�`�F���̏�����
	FenceInit();			// �t�F���X�̏�����
	DepthBufferInit();		// �[�x�o�b�t�@�̏�����
	SrvInit();				// �V�F�[�_�[���\�[�X�r���[�֘A�̏�����
	ShaderCompilerInit();	// �V�F�[�_�[�R���p�C���[�̏�����
}

void RenderBase::CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc)
{
	// SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle = srvDescHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvDescHeap->GetGPUDescriptorHandleForHeapStart();

	UINT descriptorSize = RenderBase::GetInstance()->GetDevice()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	srvCpuHandle.ptr += descriptorSize * incrementIndex;
	srvGpuHandle.ptr += descriptorSize * incrementIndex;

	texture.SetCpuHandle(srvCpuHandle);
	texture.SetGpuHandle(srvGpuHandle);

	// �V�F�[�_�[���\�[�X�r���[�ݒ�
	srvDesc.Format = textureResourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = textureResourceDesc.MipLevels;

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	RenderBase::GetInstance()->GetDevice()->
		CreateShaderResourceView(texture.buffer.Get(), &srvDesc, srvCpuHandle);

	incrementIndex++;
}

#pragma region �e������
void RenderBase::DeviceInit()
{
	HRESULT result;

	// DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// �A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter;

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
void RenderBase::CommandInit()
{
	HRESULT result;

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

	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�R�}���h�L���[�𐶐�
	result = device.Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
void RenderBase::SwapChainInit()
{
	HRESULT result;

	// ���\�[�X�̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();
	swapChainDesc.Height = NewEngineWindow::GetInstance().GetWinHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				 // �F���̏���
	swapChainDesc.SampleDesc.Count = 1;								 // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				 // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;									 // �o�b�t�@�����Q�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		 // �t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// �X���b�v�`�F�[���̐���
	ComPtr<IDXGISwapChain1> swapChain1;
	result = dxgiFactory->CreateSwapChainForHwnd
	(
		commandQueue.Get(),
		NewEngineWindow::GetInstance().GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1
	);
	swapChain1.As(&swapChain);
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // ���\�̂Q��

	// �f�X�N���v�^�q�[�v�̐���
	device.Get()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvDescHeap));

	// �o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	// �X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// �X���b�v�`�F�[������o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// �f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvDescHeap->GetCPUDescriptorHandleForHeapStart();
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
void RenderBase::FenceInit()
{
	HRESULT result;

	// �t�F���X�̐���
	result = device.Get()->CreateFence(
		fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
}
void RenderBase::DepthBufferInit()
{
	HRESULT result;

	// ���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();		// ��
	depthResourceDesc.Height = NewEngineWindow::GetInstance().GetWinHeight(); // ����
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�f�t�H���g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// �[�x�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// �[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;	// �[�x�l1.0f(�ő�l)�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g

	// ���\�[�X�̐���
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, // �[�x�l�������݂Ɏg�p
			&depthClearValue,
			IID_PPV_ARGS(&depthBuffer));
	assert(SUCCEEDED(result));

	// �[�x�r���[�p�f�X�N���v�^�q�[�v�̍쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	// �[�x�r���[�͈��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	result = RenderBase::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvDescHeap));

	// �[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvView = {};
	dsvView.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g
	dsvView.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	RenderBase::GetInstance()->GetDevice()->
		CreateDepthStencilView(
			depthBuffer.Get(),
			&dsvView,
			dsvDescHeap->GetCPUDescriptorHandleForHeapStart());
}
void RenderBase::SrvInit()
{
	HRESULT result;

	// SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// �V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = RenderBase::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvDescHeap));
	assert(SUCCEEDED(result));
}
void RenderBase::ShaderCompilerInit()
{
	// ���_�V�F�[�_�[�t�@�C���̓ǂݍ��݂ƃR���p�C���[
	{
		HRESULT result;

		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		result = D3DCompileFromFile(
			L"BasicVS.hlsl", // �V�F�[�_�t�@�C����
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
			"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
			0,
			&vsBlob, &errorBlob);

		// �V�F�[�_�̃G���[���e��\��
		if (FAILED(result))
		{
			// errorBlob����G���[���e��string�^�ɃR�s�[
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// �G���[���e���o�̓E�B���h�E�ɕ\��
			OutputDebugStringA(error.c_str());
			assert(0);
		}

		// ���_�V�F�[�_�ɓn�����߂̒��_�f�[�^�𐮂���
		inputLayout[0] =
		{	// xyz���W
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		};
		inputLayout[1] =
		{	// xyz���W
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		};
		inputLayout[2] =
		{	// uv���W
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0

		};
	}

	// 3D�p�s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	{
		HRESULT result;

		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		result = D3DCompileFromFile(
			L"BasicPS.hlsl", // �V�F�[�_�t�@�C����
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
			"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
			0,
			&ps3DBlob, &errorBlob);

		// �V�F�[�_�̃G���[���e��\��
		if (FAILED(result))
		{
			// errorBlob����G���[���e��string�^�ɃR�s�[
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// �G���[���e���o�̓E�B���h�E�ɕ\��
			OutputDebugStringA(error.c_str());
			assert(0);
		}
	}

	// 2D�p�s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	{
		HRESULT result;

		// �s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
		result = D3DCompileFromFile(
			L"BasicPS2.hlsl", // �V�F�[�_�t�@�C����
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
			"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
			0,
			&ps2DBlob, &errorBlob);

		// �V�F�[�_�̃G���[���e��\��
		if (FAILED(result))
		{
			// errorBlob����G���[���e��string�^�ɃR�s�[
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// �G���[���e���o�̓E�B���h�E�ɕ\��
			OutputDebugStringA(error.c_str());
			assert(0);
		}
	}
}

#pragma endregion

#pragma region �Q�b�^�[�֘A
ComPtr<ID3D12Device> RenderBase::GetDevice()
{
	return device;
}
ComPtr<IDXGISwapChain4> RenderBase::GetSwapChain()
{
	return swapChain;
}
ComPtr<ID3D12CommandAllocator> RenderBase::GetCommandAllocataor()
{
	return cmdAllocator;
}
ComPtr<ID3D12GraphicsCommandList> RenderBase::GetCommandList()
{
	return commandList;
}
ComPtr<ID3D12CommandQueue> RenderBase::GetCommandQueue()
{
	return commandQueue;
}
ComPtr<ID3D12DescriptorHeap> RenderBase::GetRtvHeap()
{
	return rtvDescHeap;
}
D3D12_DESCRIPTOR_HEAP_DESC RenderBase::GetRtvDescHeap()
{
	return rtvHeapDesc;
}
ComPtr<ID3D12Fence> RenderBase::GetFence()
{
	return fence;
}
UINT64 RenderBase::GetFenceVal()
{
	return fenceVal;
}
UINT64 RenderBase::PreIncreFenceVal()
{
	++fenceVal;
	return fenceVal;
}
std::vector<ComPtr<ID3D12Resource>> RenderBase::GetBackBuffers()
{
	return backBuffers;
}

// �[�x�o�b�t�@�p�f�X�N���v�^�q�[�v
ComPtr<ID3D12DescriptorHeap> RenderBase::GetDsvDescHeap()
{
	return dsvDescHeap;
}

// srv�p�f�X�N���v�^�q�[�v
ComPtr<ID3D12DescriptorHeap> RenderBase::GetSrvDescHeap()
{
	return srvDescHeap;
}

// �V�F�[�_�[�R���p�C���[�֘A
ComPtr<ID3DBlob> RenderBase::GetvsBlob()
{
	return vsBlob;
}
ComPtr<ID3DBlob> RenderBase::Getps3DBlob()
{
	return ps3DBlob;
}
ComPtr<ID3DBlob> RenderBase::Getps2DBlob()
{
	return ps2DBlob;
}
ComPtr<ID3DBlob> RenderBase::GeterrorBlob()
{
	return errorBlob;
}
D3D12_INPUT_ELEMENT_DESC* RenderBase::GetInputLayout()
{
	return inputLayout;
}
int RenderBase::GetInputLayoutSize()
{
	return sizeof(inputLayout) / sizeof(inputLayout[0]);
}



RenderBase* RenderBase::GetInstance()
{
	static RenderBase* renderBase = new RenderBase;
	return renderBase;
}
void RenderBase::DestroyInstance()
{
	delete RenderBase::GetInstance();
}
#pragma endregion