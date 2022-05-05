#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
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
	void Initialize2();
public:
	ID3D12Resource* GetTextureBuff();
	void SetImageDate(XMFLOAT4 color);
private:
	void TransferDateToTexBuff();	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]������֐�
};

