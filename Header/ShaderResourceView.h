#pragma once
#include "Header/TextureBuffer.h"
#include <d3d12.h>
#include <vector>
#include <wrl.h>

class ShaderResourceView
{
private:
	// SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	// SRV�ݒ�\����
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	UINT incrementIndex = 1;

public:
	void Initialize();
	void CreateSrv(Texture& texture, const D3D12_RESOURCE_DESC& textureResourceDesc);

public:
	// SRV�p�f�X�N���v�^�q�[�v���擾����֐�
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetSrvHeap();

	static ShaderResourceView* GetInstance();
	static void DestroyInstance();
private:
	ShaderResourceView() = default;
	~ShaderResourceView() = default;

	ShaderResourceView(const ShaderResourceView&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&) = delete;
	ShaderResourceView(const ShaderResourceView&&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&&) = delete;
};