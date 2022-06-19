#include "Header/ConstantBuffer.h"
#include "Header/NewEngineBase.h"
#include <cassert>
using namespace Microsoft::WRL;

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
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&cbHeapProp,	// ヒープの設定
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc, // リソースの設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	// 定数バッファのマッピング
	//ConstBufferDateMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	// マッピング
	assert(SUCCEEDED(result));

	// 値を書き込むと自動的に転送される
	constMapMaterial->color = { 1.0f, 1.0f, 1.0f, 1.0f };
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
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
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

ComPtr<ID3D12Resource> ConstantBuffer::GetConstBuffMaterial()
{
	return constBuffMaterial;
}
ComPtr<ID3D12Resource> ConstantBuffer::GetConstBuffTransform()
{
	return constBuffTransform;
}

void ConstantBuffer::SetColor(const Color& color)
{
	HRESULT result;

	// 定数バッファのマッピング
	//ConstBufferDateMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	// マッピング
	assert(SUCCEEDED(result));

	// 値を書き込むと自動的に転送される
	constMapMaterial->color =
	{
		color.r / 255,
		color.g / 255,
		color.b / 255,
		color.a / 255 
	};
}
