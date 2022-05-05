#pragma once
#include <d3d12.h>
#include "Vertex.h"

class VertexBuffer
{
private:
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
public:
	// ���\�[�X
	D3D12_RESOURCE_DESC resDesc{};
public:
	void Initialize(Vertex vertices[], int arrarySize);
public:
	// ���_�o�b�t�@�r���[���擾����֐�
	D3D12_VERTEX_BUFFER_VIEW* GetvbViewAddress();
	// ���_�o�b�t�@�Ƀf�[�^�]������֐�
	void TransferDateToVerBuff();	
};