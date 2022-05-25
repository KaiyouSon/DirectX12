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
	// DXGIファクトリーの生成
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// アダプターの列挙用
	std::vector<ComPtr<IDXGIAdapter4>> adapters;

	// パフォーマンスが高いものから順に、全てのアダプターを列挙する
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++)
	{
		// 動的配列に追加する
		adapters.push_back(tmpAdapter);
	}

	// 妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);
		// ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			// デバイスを採用してループを抜ける
			tmpAdapter = adapters[i].Get();
			break;
		}
	}
}
void NewEngineBase::DeviceInit()
{
	//----------------------------- デバイスの生成 -----------------------------//
	// 対応レベルの配列
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
		// 採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(device.GetAddressOf()));
		if (result == S_OK) {
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}
}
void NewEngineBase::CommandListInit()
{
	// コマンドアロケータを生成
	result = device.Get()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));
	assert(SUCCEEDED(result));
	// コマンドリストを生成
	result = device.Get()->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));
}
void NewEngineBase::CommandQueueInit()
{
	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//コマンドキューを生成
	result = device.Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
void NewEngineBase::SwapChainInit()
{
	//------------------------- スワップチェーンの生成 -------------------------//
	// スワップチェーンの設定
	swapChainDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();
	swapChainDesc.Height = NewEngineWindow::GetInstance().GetWinHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 色情報の書式
	swapChainDesc.SampleDesc.Count = 1; // マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // バックバッファ用
	swapChainDesc.BufferCount = 2; // バッファ数を２つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// スワップチェーンの生成
	ComPtr<IDXGISwapChain1> swapChain1;
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(), NewEngineWindow::GetInstance().GetHwnd(), &swapChainDesc, nullptr, nullptr,
		&swapChain1);
	swapChain1.As(&swapChain);
	assert(SUCCEEDED(result));
}
void NewEngineBase::DescriptorHeapInit()
{
	// デスクリプタヒープの設定
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // 裏表の２つ
	// デスクリプタヒープの生成
	device.Get()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
}
void NewEngineBase::BackBufferInit()
{
	//----------------------------- バックバッファ -----------------------------//
	// バックバッファ
	backBuffers.resize(swapChainDesc.BufferCount);
}
void NewEngineBase::RenderTargetViewInit()
{
	//------------------ レンダーターゲットビュー(RTV)の生成 -------------------//
	for (size_t i = 0; i < backBuffers.size(); i++)
		// スワップチェーンの全てのバッファについて処理する
	{
		// スワップチェーンからバッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// デスクリプタヒープのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		// 裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device.Get()->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// レンダーターゲットビューの設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		// シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// レンダーターゲットビューの生成
		device.Get()->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}
void NewEngineBase::FenceInit()
{
	// フェンスの生成
	result = device.Get()->CreateFence(
		fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
}

#pragma region // ------------------------- ゲッター関連 ------------------------- //
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