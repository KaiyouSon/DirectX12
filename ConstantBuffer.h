#pragma once
#include <d3d12.h>
#include <DirectXMath.h>

using namespace DirectX;

// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDateMaterial
{
	XMFLOAT4 color;	// �F(RGBA)
};

// �萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
struct ConstBufferDataTransform
{
	XMMATRIX mat;	//3D�ϊ��s��
};

class ConstantBuffer
{
private:
	ID3D12Resource* constBuffMaterial;	// �}�e���A���̒萔�o�b�t�@
	ID3D12Resource* constBuffTransform;	// �g�����X�t�H�[���̒萔�o�b�t�@

public:
	ConstBufferDataTransform* constMapTransform = nullptr;
public:
	void MaterialBufferInit();
	void TransformBufferInit();
public:
	ID3D12Resource* GetConstBuffMaterial();
	ID3D12Resource* GetConstBuffTransform();

	void SetColor(XMFLOAT4 color);
};