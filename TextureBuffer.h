#pragma once
#include "MathUtil.h"
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <DirectXTex.h>

class Texture
{
private:
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = D3D12_CPU_DESCRIPTOR_HANDLE(); //SRVのハンドル(CPU側)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = D3D12_GPU_DESCRIPTOR_HANDLE(); //SRVのハンドル(GPU側)
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer; //テクスチャのリソース

	void SetCpuHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle);
	void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle();
};

class TextureBuffer
{
private:
	static const size_t textureWidth = 256;	// 横方向ピクセル数
	static const size_t textureHeight = 256;	// 縦方向ピクセル数
	static const size_t imageDataCount = textureWidth * textureHeight;	// 配列の要素数
	static Vec4* imageData;	// 画像イメージデータ配列

public:
	~TextureBuffer();
	static Texture LoadTexture(const std::string filePath);
	static Texture GetDefaultTexture();
};

