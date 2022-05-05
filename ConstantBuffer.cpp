#include "ConstantBuffer.h"
#include "NewEngineBase.h"

#include <cassert>

extern NewEngineBase* newEngine;

void ConstantBuffer::MaterialBufferInit()
{
	// ヒープの設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDateMaterial) + 0xff) & ~0xff; // 256バイトアラインメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// 定数バッファの生成
	result = newEngine->GetDevice()->CreateCommittedResource(
		&cbHeapProp,	// ヒープの設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc, // リソースの設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	// 定数バッファのマッピング
	ConstBufferDateMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	// マッピング
	assert(SUCCEEDED(result));

	// 値を書き込むと自動的に転送される
	constMapMaterial->color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// RGBAで半透明の赤
}

void ConstantBuffer::TransformBufferInit()
{
	// ヒープの設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff; // 256バイトアラインメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// 定数バッファの生成
	result = newEngine->GetDevice()->CreateCommittedResource(
		&cbHeapProp,	// ヒープの設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc, // リソースの設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform));
	assert(SUCCEEDED(result));

	// 定数バッファのマッピング
	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);	// マッピング
	assert(SUCCEEDED(result));
}

ID3D12Resource* ConstantBuffer::GetConstBuffMaterial()
{
	return constBuffMaterial;
}

ID3D12Resource* ConstantBuffer::GetConstBuffTransform()
{
	return constBuffTransform;
}
