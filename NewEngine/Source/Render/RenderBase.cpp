#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Render/Viewport.h"
#include "NewEngine/Header/Render/ScissorRectangle.h"
#include <cassert>
#include <string>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
using namespace Microsoft::WRL;

Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

void RenderBase::Initialize()
{
	DeviceInit();			// デバイスの初期化
	CommandInit();			// コマンド関連の初期化
	SwapChainInit();		// スワップチェンの初期化
	FenceInit();			// フェンスの初期化
	DepthBufferInit();		// 深度バッファの初期化
	SrvInit();				// シェーダーリソースビュー関連の初期化
	ShaderCompilerInit();	// シェーダーコンパイラーの初期化
	RootSignatureInit();	// ルードシグネチャーの初期化
	GraphicsPipelineInit();	// グラフィックスパイプラインの初期化
}

void RenderBase::PreDraw()
{
	//---------------------- リソースバリアの変更コマンド ----------------------//
	// バックバッファの番号を取得（2つなので0番か1番）
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
	// １．リソースバリアで書き込み可能に変更
	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get();	// バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;	// 表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	//--------------------------- 描画先指定コマンド ---------------------------//
	// ２．描画先の変更
	// レンダーターゲットビューのハンドルを取得
	rtvHandle = rtvDescHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);

	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvDescHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 画面クリア R G B A
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	// 深度バッファクリア
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// ルートシグネチャの設定コマンド
	commandList->SetGraphicsRootSignature(rootSignature.Get());

	// プリミティブ形状の設定コマンド
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// ビューポートの処理
	viewport->Update();

	// シザー矩形の処理
	scissorRectangle->Update();
}
void RenderBase::Draw3D()
{
	// パイプラインステートの設定コマンド( 3D版 )
	commandList->SetPipelineState(pipelineState3D.Get());
}
void RenderBase::Draw2D()
{
	// パイプラインステートの設定コマンド( 2D版 )
	commandList->SetPipelineState(pipelineState2D.Get());
}
void RenderBase::PostDraw()
{
	HRESULT result;

	//---------------------- リソースバリアの復帰コマンド ----------------------//
	// ５．リソースバリアを戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // 表示状態へ
	commandList->ResourceBarrier(1, &barrierDesc);

	//-------------------------- コマンドのフラッシュ --------------------------//
	// 命令のクローズ
	result = commandList->Close();
	assert(SUCCEEDED(result));
	// コマンドリストの実行
	ID3D12CommandList* commandLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ（裏表の入替え）
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	// コマンドの実行完了を待つ
	commandQueue->Signal(fence.Get(), ++fenceVal);
	//RenderBase::GetInstance()->PreIncreFenceVal());
	if (fence.Get()->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// キューをクリア
	result = commandAllocator->Reset();
	assert(SUCCEEDED(result));
	// 再びコマンドリストを貯める準備
	result = commandList.Get()->Reset(commandAllocator.Get(), nullptr);
	assert(SUCCEEDED(result));
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
	result = device->CreateCommandAllocator
	(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)
	);
	assert(SUCCEEDED(result));

	// コマンドリストを生成
	result = device->CreateCommandList
	(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList)
	);
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
	swapChainDesc.Width = RenderWindow::GetInstance().GetWinWidth();
	swapChainDesc.Height = RenderWindow::GetInstance().GetWinHeight();
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
		RenderWindow::GetInstance().GetHwnd(),
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
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvDescHeap));

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
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}
void RenderBase::FenceInit()
{
	HRESULT result;

	// フェンスの生成
	result = device->CreateFence(
		fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
}
void RenderBase::DepthBufferInit()
{
	HRESULT result;

	// リソースの設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = RenderWindow::GetInstance().GetWinWidth();		// 幅
	depthResourceDesc.Height = RenderWindow::GetInstance().GetWinHeight(); // 高さ
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
	result = device->CreateCommittedResource
	(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度値書き込みに使用
		&depthClearValue,
		IID_PPV_ARGS(&depthBuffer)
	);
	assert(SUCCEEDED(result));

	// 深度ビュー用デスクリプタヒープの作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	// 深度ビューは一つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvDescHeap));

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvView = {};
	dsvView.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット
	dsvView.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView
	(
		depthBuffer.Get(),
		&dsvView,
		dsvDescHeap->GetCPUDescriptorHandleForHeapStart()
	);
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
	result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvDescHeap));
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
void RenderBase::RootSignatureInit()
{
	HRESULT result;

	// デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1;			// 一度の描画に使うテクスチャが1枚なので１
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;		// テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 横繰り返し(タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 縦繰り返し(タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					// 奥行繰り返し(タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;	// ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;					// 全てのリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;									// ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;												// ミップマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;			// ピクセルシェーダからのみ使用可能

	// ルートパラメーターの設定
	D3D12_ROOT_PARAMETER rootParams[3] = {};
	// 定数バッファの0番
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	// 種類
	rootParams[0].Descriptor.ShaderRegister = 0;					// 定数バッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;						// デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	// 全てのシェーダから見える
	// テクスチャレジスタ0番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // 種類
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;		  // デスクリプタレンジ
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;					  // デスクリプタレンジ数
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;			  // 全てのシェーダから見える
	// 定数バッファの1番
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;	// 種類
	rootParams[2].Descriptor.ShaderRegister = 1;					// 定数バッファ番号
	rootParams[2].Descriptor.RegisterSpace = 0;						// デフォルト値
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;	// 全てのシェーダから見える

	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;	// ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = _countof(rootParams);		// ルートパラメータ数
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;
	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	result = D3D12SerializeRootSignature(
		&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob,
		&errorBlob);
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature
	(
		0,
		rootSigBlob->GetBufferPointer(),
		rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature)
	);
	assert(SUCCEEDED(result));
}
void RenderBase::GraphicsPipelineInit()
{
	// グラフィックスパイプライン3D用
	{
		// グラフィックスパイプライン設定
		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

		// シェーダーの設定
		pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
		pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
		pipelineDesc.PS.pShaderBytecode = ps3DBlob->GetBufferPointer();
		pipelineDesc.PS.BytecodeLength = ps3DBlob->GetBufferSize();

		// サンプルマスクの設定
		pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

		// ラスタライザの設定
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// 背面をカリング
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// ポリゴン内塗りつぶし
		pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

		// デプスステンシルステートの設定
		pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テストを行う
		pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;	// 書き込み許可
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	// 小さいほうを採用
		pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット

		// ブレンドステート
		//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask =
		//	D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

		// レンダーターゲットのブレンド設定
		D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = pipelineDesc.BlendState.RenderTarget[0];
		blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		blendDesc.BlendEnable = true;					// ブレンドを有効にする
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	// 加算
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;		// ソースの値を100％使う
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;	// デストの値を  0％使う

		// 加算合成
		//blendDesc.BlendOp = D3D12_BLEND_OP_ADD;	// 加算
		//blendDesc.SrcBlend = D3D12_BLEND_ONE;		// ソースの値を100％使う
		//blendDesc.DestBlend = D3D12_BLEND_ONE;	// デストの値を100％使う

		// 減算合成
		//blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;	// デストからソースを減算
		//blendDesc.SrcBlend = D3D12_BLEND_ONE;				// ソースの値を100％使う
		//blendDesc.DestBlend = D3D12_BLEND_ONE;			// デストの値を100％使う

		// 色反転
		//blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
		//blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;		// 1.0f-デストカラーの値
		//blendDesc.DestBlend = D3D12_BLEND_ZERO;				// 使わない

		// 半透明合成
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			// ソースのアルファ値
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;		// 1.0f-ソースのアルファ値

		// 頂点レイアウトの設定
		pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
		pipelineDesc.InputLayout.NumElements = sizeof(inputLayout) / sizeof(inputLayout[0]);

		// 図形の形状設定
		pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// その他の設定
		pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
		pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
		pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

		// パイプラインにルートシグネチャをセット
		pipelineDesc.pRootSignature = rootSignature.Get();

		HRESULT result;

		// パイプランステートの生成
		result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState3D));
		assert(SUCCEEDED(result));
	}

	// グラフィックスパイプライン2D用
	{
		// グラフィックスパイプライン設定
		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

		// シェーダーの設定
		pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
		pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
		pipelineDesc.PS.pShaderBytecode = ps2DBlob->GetBufferPointer();
		pipelineDesc.PS.BytecodeLength = ps2DBlob->GetBufferSize();

		// サンプルマスクの設定
		pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

		// ラスタライザの設定
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	// 背面をカリング
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// ポリゴン内塗りつぶし
		pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

		// ブレンドステート
		//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask =
		//	D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

		// レンダーターゲットのブレンド設定
		D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
		blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		blenddesc.BlendEnable = true;					// ブレンドを有効にする
		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	// 加算
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		// ソースの値を100％使う
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	// デストの値を  0％使う

		// 加算合成
		//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	// 加算
		//blenddesc.SrcBlend = D3D12_BLEND_ONE;		// ソースの値を100％使う
		//blenddesc.DestBlend = D3D12_BLEND_ONE;	// デストの値を100％使う

		// 減算合成
		//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;	// デストからソースを減算
		//blenddesc.SrcBlend = D3D12_BLEND_ONE;				// ソースの値を100％使う
		//blenddesc.DestBlend = D3D12_BLEND_ONE;			// デストの値を100％使う

		// 色反転
		//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
		//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;		// 1.0f-デストカラーの値
		//blenddesc.DestBlend = D3D12_BLEND_ZERO;				// 使わない

		// 半透明合成
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			// ソースのアルファ値
		blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;		// 1.0f-ソースのアルファ値

		// 頂点レイアウトの設定
		pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
		pipelineDesc.InputLayout.NumElements = sizeof(inputLayout) / sizeof(inputLayout[0]);

		// 図形の形状設定
		pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		// その他の設定
		pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
		pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
		pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

		// パイプラインにルートシグネチャをセット
		pipelineDesc.pRootSignature = rootSignature.Get();

		HRESULT result;

		// パイプランステートの生成
		result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState2D));
		assert(SUCCEEDED(result));
	}
}
#pragma endregion

#pragma region ゲッター関連
// デバイス
ComPtr<ID3D12Device> RenderBase::GetDevice()
{
	return device;
}

// コマンド関連
ComPtr<ID3D12GraphicsCommandList> RenderBase::GetCommandList()
{
	return commandList;
}

// srv用デスクリプタヒープ
ComPtr<ID3D12DescriptorHeap> RenderBase::GetSrvDescHeap()
{
	return srvDescHeap;
}

// シングルトン関連
RenderBase* RenderBase::GetInstance()
{
	static RenderBase* renderBase = new RenderBase;
	return renderBase;
}
void RenderBase::DestroyInstance()
{
	delete RenderBase::GetInstance();
	delete viewport;
	delete scissorRectangle;
}
#pragma endregion
