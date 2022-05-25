#pragma once
#include "MathUtil.h"
#include <d3d12.h>
#include <string.h>
#include <wrl.h>
#include <DirectXTex.h>

class Texture
{
public:
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	static Texture LoadTexture(const wchar_t* FilePath);
};

class TextureBuffer
{
private:
	// �������s�N�Z����
	const size_t textureWidth = 256;
	// �c�����s�N�Z����
	const size_t textureHeight = 256;
	// �z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;
	// �摜�C���[�W�f�[�^�z��
	Vec4* imageData = new Vec4[imageDataCount];
	// �e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

public:
	~TextureBuffer();
	void Initialize1();
	void Initialize2(const wchar_t* szFile);
	void Initialize3(const Texture& texture);
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuff();
};

