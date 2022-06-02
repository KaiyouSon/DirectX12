#include "TextureBuffer.h"
#include "NewEngineBase.h"
#include "ShaderResourceView.h"
#include <cassert>
using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

Vec4* TextureBuffer::imageData = new Vec4[imageDataCount];

TextureBuffer::~TextureBuffer()
{
	delete[] imageData;
}

// テクスチャのロード
Texture TextureBuffer::LoadTexture(const string filePath)
{
	HRESULT result;
	Texture texture;
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	wstring wfilePath(filePath.begin(), filePath.end());

	// WICテクスチャのロード
	result = LoadFromWICFile(
		wfilePath.c_str(),
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// ミップマップ生成
	ScratchImage mipChain{};
	result = GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
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
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texture.buffer));
	assert(SUCCEEDED(result));

	// 全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// 全ミップマップレベルを指定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = texture.buffer->WriteToSubresource(
			(UINT)i,
			nullptr,				// 全領域へコピー
			img->pixels,			// 元データアドレス
			(UINT)img->rowPitch,	// １ラインサイズ
			(UINT)img->slicePitch	// １枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	ShaderResourceView::GetInstance()->CreateSrv(texture, textureResourceDesc);

	return texture;
}

// デフォルトのテクスチャ
Texture TextureBuffer::GetDefaultTexture()
{
	HRESULT result;
	Texture texture;

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

	// テクスチャバッファの生成
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&textureHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&textureResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texture.buffer));
	assert(SUCCEEDED(result));

	// テクスチャバッファにデータ転送
	result = texture.buffer->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		imageData,	// 元データアドレス
		sizeof(Vec4) * textureWidth, // 1ラインサイズ
		sizeof(Vec4) * imageDataCount // 全サイズ
	);

	ShaderResourceView::GetInstance()->CreateSrv(texture, textureResourceDesc);

	return texture;
}

void Texture::SetCpuHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle)
{
	this->cpuHandle = cpuHandle;
}

void Texture::SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle)
{
	this->gpuHandle = gpuHandle;
}

D3D12_GPU_DESCRIPTOR_HANDLE Texture::GetGpuHandle()
{
	return gpuHandle;
}