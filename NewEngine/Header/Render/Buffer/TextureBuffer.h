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
	static const size_t textureWidth = 256;	// �������s�N�Z����
	static const size_t textureHeight = 256;	// �c�����s�N�Z����
	static const size_t imageDataCount = textureWidth * textureHeight;	// �z��̗v�f��
	static Vec4* imageData;	// �摜�C���[�W�f�[�^�z��

public:
	~TextureBuffer();
	static Texture* LoadTexture(const std::string filePath);
	static Texture GetDefaultTexture();
	static void UnLoadTexture(Texture* texture);
};

