#include "TextureBuffer.h"
#include "NewEngineBase.h"
#include <cassert>
#include <DirectXTex.h>
using namespace DirectX;
using namespace Microsoft::WRL;

TextureBuffer::~TextureBuffer()
{
	delete[] imageData;
}

void TextureBuffer::Initialize1()
{
	// 全てのピクセルの色の初期化
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].x = 1.0f;	// R
		imageData[i].y = 1.0f;	// G
		imageData[i].z = 1.0f;	// B
		imageData[i].w = 1.0f;	// A
	}

	// ヒープの設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureResourceDesc.Width = textureWidth; // 幅
	textureResourceDesc.Height = textureWidth; // 高さ
	textureResourceDesc.DepthOrArraySize = 1;
	textureResourceDesc.MipLevels = 1;
	textureResourceDesc.SampleDesc.Count = 1;

	HRESULT result;

	// テクスチャバッファの生成
	result = NewEngineBase::GetInstance().GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	// テクスチャバッファにデータ転送
	result = texBuff->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		imageData,	// 元データアドレス
		sizeof(Vec4) * textureWidth, // 1ラインサイズ
		sizeof(Vec4) * imageDataCount // 全サイズ
	);
}

void TextureBuffer::Initialize2(const wchar_t* szFile)
{
	HRESULT result;

	// 画像ファイルの用意
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	// WICテクスチャのロード
	result = LoadFromWICFile(
		szFile,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	if (result != S_OK) Initialize1();

	if (result == S_OK)
	{
		ScratchImage mipChain{};
		// ミップマップ生成
		result = GenerateMipMaps(
			scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
			TEX_FILTER_DEFAULT, 0, mipChain);
		if (SUCCEEDED(result))
		{
			scratchImg = std::move(mipChain);
			metadata = scratchImg.GetMetadata();
		}

		// 読み込んだディフューズテクスチャをSRGBとして扱う
		metadata.format = MakeSRGB(metadata.format);

		// ヒープの設定
		D3D12_HEAP_PROPERTIES textureHeapProp{};
		textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
		textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

		// リソース設定
		D3D12_RESOURCE_DESC textureResourceDesc{};
		textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		textureResourceDesc.Format = metadata.format;
		textureResourceDesc.Width = metadata.width; // 幅
		textureResourceDesc.Height = (UINT)metadata.height; // 高さ
		textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
		textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
		textureResourceDesc.SampleDesc.Count = 1;

		// テクスチャバッファの生成
		result = NewEngineBase::GetInstance().GetDevice()->
			CreateCommittedResource(
				&textureHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&textureResourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&texBuff));
		assert(SUCCEEDED(result));

		// 全ミップマップについて
		for (size_t i = 0; i < metadata.mipLevels; i++)
		{
			// 全ミップマップレベルを指定してイメージを取得
			const Image* img = scratchImg.GetImage(i, 0, 0);
			// テクスチャバッファにデータ転送
			result = texBuff->WriteToSubresource(
				(UINT)i,
				nullptr,				// 全領域へコピー
				img->pixels,			// 元データアドレス
				(UINT)img->rowPitch,	// １ラインサイズ
				(UINT)img->slicePitch	// １枚サイズ
			);
			assert(SUCCEEDED(result));
		}
	}
}

ComPtr<ID3D12Resource> TextureBuffer::GetTextureBuff()
{
	return texBuff;
}