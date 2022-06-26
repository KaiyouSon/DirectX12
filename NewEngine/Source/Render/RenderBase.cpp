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
	DeviceInit();			// デバイスの初期化
	CommandInit();			// コマンド関連の初期化
	SwapChainInit();		// スワップチェンの初期化
	FenceInit();			// フェンスの初期化
	DepthBufferInit();		// 深度バッファの初期化
	SrvInit();				// シェーダーリソースビュー関連の初期化
	ShaderCompilerInit();	// シェーダーコンパイラーの初期化
}

void RenderBase::CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc)
{
	// SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle = srvDescHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvDescHeap->GetGPUDescriptorHandleForHeapStart();

	UINT descriptorSize = RenderBase::GetInstance()->GetDevice()->
		GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	srvCpuHandle.ptr += descriptorSize * incrementIndex;
	srvGpuHandle.ptr += descriptorSize * incrementIndex;

	texture.SetCpuHandle(srvCpuHandle);
	texture.SetGpuHandle(srvGpuHandle);

	// シェーダーリソースビュー設定
	srvDesc.Format = textureResourceDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = textureResourceDesc.MipLevels;

	// ハンドルの指す位置にシェーダーリソースビュー作成
	RenderBase::GetInstance()->GetDevice()->
		CreateShaderResourceView(texture.buffer.Get(), &srvDesc, srvCpuHandle);

	incrementIndex++;
}

#pragma region 各初期化
void RenderBase::DeviceInit()
{
	HRESULT result;

	// DXGIファクトリーの生成
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// アダプターの列挙用
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	// ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter;

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
void RenderBase::CommandInit()
{
	HRESULT result;

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

	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//コマンドキューを生成
	result = device.Get()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
void RenderBase::SwapChainInit()
{
	HRESULT result;

	// リソースの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();
	swapChainDesc.Height = NewEngineWindow::GetInstance().GetWinHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				 // 色情報の書式
	swapChainDesc.SampleDesc.Count = 1;								 // マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				 // バックバッファ用
	swapChainDesc.BufferCount = 2;									 // バッファ数を２つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		 // フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// スワップチェーンの生成
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

	// デスクリプタヒープの設定
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; // 裏表の２つ

	// デスクリプタヒープの生成
	device.Get()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvDescHeap));

	// バックバッファ
	backBuffers.resize(swapChainDesc.BufferCount);

	// スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		// スワップチェーンからバッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		// デスクリプタヒープのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvDescHeap->GetCPUDescriptorHandleForHeapStart();
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
void RenderBase::FenceInit()
{
	HRESULT result;

	// フェンスの生成
	result = device.Get()->CreateFence(
		fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
}
void RenderBase::DepthBufferInit()
{
	HRESULT result;

	// リソースの設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = NewEngineWindow::GetInstance().GetWinWidth();		// 幅
	depthResourceDesc.Height = NewEngineWindow::GetInstance().GetWinHeight(); // 高さ
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値デフォルト
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// 深度用ヒーププロパティ
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// 深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;	// 深度値1.0f(最大値)でクリア
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット

	// リソースの生成
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度値書き込みに使用
			&depthClearValue,
			IID_PPV_ARGS(&depthBuffer));
	assert(SUCCEEDED(result));

	// 深度ビュー用デスクリプタヒープの作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	// 深度ビューは一つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	result = RenderBase::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvDescHeap));

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvView = {};
	dsvView.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット
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

	// SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// シェーダから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	// 設定を元にSRV用デスクリプタヒープを生成
	result = RenderBase::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvDescHeap));
	assert(SUCCEEDED(result));
}
void RenderBase::ShaderCompilerInit()
{
	// 頂点シェーダーファイルの読み込みとコンパイラー
	{
		HRESULT result;

		// 頂点シェーダの読み込みとコンパイル
		result = D3DCompileFromFile(
			L"BasicVS.hlsl", // シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
			"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
			0,
			&vsBlob, &errorBlob);

		// シェーダのエラー内容を表示
		if (FAILED(result))
		{
			// errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		}

		// 頂点シェーダに渡すための頂点データを整える
		inputLayout[0] =
		{	// xyz座標
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		};
		inputLayout[1] =
		{	// xyz座標
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		};
		inputLayout[2] =
		{	// uv座標
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0

		};
	}

	// 3D用ピクセルシェーダファイルの読み込みとコンパイル
	{
		HRESULT result;

		// ピクセルシェーダの読み込みとコンパイル
		result = D3DCompileFromFile(
			L"BasicPS.hlsl", // シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
			"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
			0,
			&ps3DBlob, &errorBlob);

		// シェーダのエラー内容を表示
		if (FAILED(result))
		{
			// errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		}
	}

	// 2D用ピクセルシェーダファイルの読み込みとコンパイル
	{
		HRESULT result;

		// ピクセルシェーダファイルの読み込みとコンパイル
		result = D3DCompileFromFile(
			L"BasicPS2.hlsl", // シェーダファイル名
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
			"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
			0,
			&ps2DBlob, &errorBlob);

		// シェーダのエラー内容を表示
		if (FAILED(result))
		{
			// errorBlobからエラー内容をstring型にコピー
			std::string error;
			error.resize(errorBlob->GetBufferSize());
			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				error.begin());
			error += "\n";
			// エラー内容を出力ウィンドウに表示
			OutputDebugStringA(error.c_str());
			assert(0);
		}
	}
}

#pragma endregion

#pragma region ゲッター関連
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

// 深度バッファ用デスクリプタヒープ
ComPtr<ID3D12DescriptorHeap> RenderBase::GetDsvDescHeap()
{
	return dsvDescHeap;
}

// srv用デスクリプタヒープ
ComPtr<ID3D12DescriptorHeap> RenderBase::GetSrvDescHeap()
{
	return srvDescHeap;
}

// シェーダーコンパイラー関連
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