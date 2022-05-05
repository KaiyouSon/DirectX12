#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
using namespace DirectX;

class TextureBuffer
{
private:
	// 横方向ピクセル数
	const size_t textureWidth = 256;
	// 縦方向ピクセル数
	const size_t textureHeight = 256;
	// 配列の要素数
	const size_t imageDataCount = textureWidth * textureHeight;
	// 画像イメージデータ配列
	XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];
	// テクスチャバッファ
	ID3D12Resource* texBuff = nullptr;
public:
	~TextureBuffer();
	void Initialize1();
	void Initialize2();
public:
	ID3D12Resource* GetTextureBuff();
	void SetImageDate(XMFLOAT4 color);
private:
	void TransferDateToTexBuff();	// テクスチャバッファにデータ転送する関数
};

