#include "DepthBuffer.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include <cassert>

using namespace Microsoft::WRL;

void DepthBuffer::Initialize()
{
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

	HRESULT result;

	// リソースの生成
	ID3D12Resource* depthBuff = nullptr;
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度値書き込みに使用
			&depthClearValue,
			IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	// 深度ビュー用デスクリプタヒープの作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;	// 深度ビューは一つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	// 深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	NewEngineBase::GetInstance().GetDevice()->
		CreateDepthStencilView(
			depthBuff,
			&dsvDesc,
			dsvHeap->GetCPUDescriptorHandleForHeapStart());

}

ComPtr<ID3D12DescriptorHeap> DepthBuffer::GetDsvHeap()
{
	return dsvHeap;
}

DepthBuffer& DepthBuffer::GetInstance()
{
	static DepthBuffer depthBuffer;
	return depthBuffer;
}