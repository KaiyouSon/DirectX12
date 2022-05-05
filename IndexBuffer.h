#pragma once
#include <d3d12.h>
#include <stdint.h>

class IndexBuffer
{
private:
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView{};
public:
	void Initialize(uint16_t indices[], int arrarySize);
public:
	// �C���f�b�N�X�o�b�t�@�r���[���擾����֐�
	D3D12_INDEX_BUFFER_VIEW* GetibViewAddress();

};

