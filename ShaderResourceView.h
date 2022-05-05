#pragma once
#include <d3d12.h>

class ShaderResourceView
{
private:
	// SRV�q�[�v�̐擪�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;
	// SRV�p�f�X�N���v�^�q�[�v
	ID3D12DescriptorHeap* srvHeap;
	// SRV�ݒ�\����
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
public:
	void Initialize();
public:
	// SRV�q�[�v�̐擪�n���h�����擾����֐�
	D3D12_CPU_DESCRIPTOR_HANDLE GetsrvHandle();

	// SRV�p�f�X�N���v�^�q�[�v���擾����֐�
	ID3D12DescriptorHeap* GetsrvHeap();

	// SRV�p�f�X�N���v�^�q�[�v�̃A�h���X���擾����֐�
	ID3D12DescriptorHeap** GetsrvHeapAddress();

	// SRV�ݒ�\���̂̃A�h���X���擾����֐�
	D3D12_SHADER_RESOURCE_VIEW_DESC* GetsrvDescAddress();
};