#pragma once
#include "Square.h"
#include "Cube.h"

#include <d3d12.h>
#include <vector>

class ShaderResourceView
{
private:
	// SRV�q�[�v�̐擪�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// SRV�p�f�X�N���v�^�q�[�v
	ID3D12DescriptorHeap* srvHeap;
	// SRV�ݒ�\����
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	// srvCpuHandle�̃|�C���^���i�[����ϐ�
	std::vector <D3D12_CPU_DESCRIPTOR_HANDLE> srvCpuHandlePtr;

	UINT incrementIndex = 0;

private:

public:
	void Initialize();
	void CreatSrv(Square& square);
	void CreatSrv(Cube& cube);

public:

	// SRV�p�f�X�N���v�^�q�[�v���擾����֐�
	ID3D12DescriptorHeap* GetSrvHeap();

	// SRV�p�f�X�N���v�^�q�[�v�̃A�h���X���擾����֐�
	ID3D12DescriptorHeap** GetSrvHeapAddress();

	D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGpuHandle();

	static ShaderResourceView& GetInstance();

private:
	ShaderResourceView() = default;
	~ShaderResourceView() = default;

	ShaderResourceView(const ShaderResourceView&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&) = delete;
	ShaderResourceView(const ShaderResourceView&&) = delete;
	ShaderResourceView& operator=(const ShaderResourceView&&) = delete;
};