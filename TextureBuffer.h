#pragma once
#include "MathUtil.h"
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <DirectXTex.h>

class Texture
{
private:
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = D3D12_CPU_DESCRIPTOR_HANDLE(); //SRV�̃n���h��(CPU��)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = D3D12_GPU_DESCRIPTOR_HANDLE(); //SRV�̃n���h��(GPU��)
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer; //�e�N�X�`���̃��\�[�X

	void SetCpuHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle);
	void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle();
};

class TextureBuffer
{
private:
	static const size_t textureWidth = 256;	// �������s�N�Z����
	static const size_t textureHeight = 256;	// �c�����s�N�Z����
	static const size_t imageDataCount = textureWidth * textureHeight;	// �z��̗v�f��
	static Vec4* imageData;	// �摜�C���[�W�f�[�^�z��

public:
	~TextureBuffer();
	static Texture LoadTexture(const std::string filePath);
	static Texture GetDefaultTexture();
};

