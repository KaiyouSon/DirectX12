#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Vertex.h"

class VertexBuffer
{
private:
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	Vertex* vertices;
	int arrarySize;
public:
	// ���\�[�X
	D3D12_RESOURCE_DESC resDesc{};
public:
	void Initialize(Vertex vertices[], int arrarySize);
public:
	// ���_�o�b�t�@�r���[���擾����֐�
	D3D12_VERTEX_BUFFER_VIEW* GetvbViewAddress();
	void TransferToBuffer();
	void Unmap();
};