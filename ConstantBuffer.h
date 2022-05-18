#pragma once
#include "Mat4.h"
#include "Vec4.h"
#include <d3d12.h>

// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDateMaterial
{
	Vec4 color;	// �F(RGBA)
};

// �萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
struct ConstBufferDataTransform
{
	Mat4 mat;	//3D�ϊ��s��
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

	void SetColor(Vec4 color);
};