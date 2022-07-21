#pragma once
#include "NewEngine/Header/Render/Vertex.h"
#include <vector>
#include <d3d12.h>
#include <wrl.h>

class VertexBuffer
{
private:
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	std::vector<Vertex> vertices;
	int arrarySize;
public:
	// ���\�[�X
	D3D12_RESOURCE_DESC resDesc{};
public:
	void Initialize(Vertex vertices[], int arrarySize);
	void Initialize(std::vector<Vertex> vertices);
	void Initialize(std::vector<Vertex2> vertices);
public:
	// ���_�o�b�t�@�r���[���擾����֐�
	D3D12_VERTEX_BUFFER_VIEW* GetvbViewAddress();
	void TransferToBuffer(std::vector<Vertex> vertices);
	void TransferToBuffer();
	void Unmap();
};