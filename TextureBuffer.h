#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <string.h>
using namespace DirectX;

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
	XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];
	// �e�N�X�`���o�b�t�@
	ID3D12Resource* texBuff = nullptr;
public:
	~TextureBuffer();
	void Initialize1();
	void Initialize2(const wchar_t* szFile);
public:
	ID3D12Resource* GetTextureBuff();
};

