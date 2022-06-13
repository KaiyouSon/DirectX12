#pragma once
#include "Color.h"
#include "MathUtil.h"
#include <d3d12.h>
#include <wrl.h>

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
	// �}�e���A���̒萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	// �g�����X�t�H�[���̒萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;

	ConstBufferDateMaterial* constMapMaterial;

public:
	ConstBufferDataTransform* constMapTransform = nullptr;
public:
	void MaterialBufferInit();
	void TransformBufferInit();
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> GetConstBuffMaterial();
	Microsoft::WRL::ComPtr<ID3D12Resource> GetConstBuffTransform();

	void SetColor(const Color& color);
};