#pragma once
#include "NewEngine/Header/Developer/Component/Texture.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <DirectXTex.h>

class TextureBuffer
{
private:
	static const size_t textureWidth = 256;	// 横方向ピクセル数
	static const size_t textureHeight = 256;	// 縦方向ピクセル数
	static const size_t imageDataCount = textureWidth * textureHeight;	// 配列の要素数
	static Vec4* imageData;	// 画像イメージデータ配列

public:
	~TextureBuffer();
	static Texture* LoadTexture(const std::string filePath);
	static Texture GetDefaultTexture();
	static void UnLoadTexture(Texture* texture);
};

