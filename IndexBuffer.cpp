#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "NewEngineBase.h"

#include <cassert>

extern NewEngineBase* newEngine;
extern VertexBuffer* vertexBuffer;

void IndexBuffer::Initialize(uint16_t indices[], int arrarySize)
{
	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * arrarySize);

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	vertexBuffer->resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexBuffer->resDesc.Width = sizeIB; // ���_�f�[�^�S�̂̃T�C�Y
	vertexBuffer->resDesc.Height = 1;
	vertexBuffer->resDesc.DepthOrArraySize = 1;
	vertexBuffer->resDesc.MipLevels = 1;
	vertexBuffer->resDesc.SampleDesc.Count = 1;
	vertexBuffer->resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// �C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff = nullptr;
	result = newEngine->GetDevice()->CreateCommittedResource(
		&heapProp, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&vertexBuffer->resDesc, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));
	assert(SUCCEEDED(result));

	//------------------- �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]�� -------------------//
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < arrarySize; i++)
	{
		indexMap[i] = indices[i]; // ���W���R�s�[
	}
	// �q���������
	indexBuff->Unmap(0, nullptr);

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

D3D12_INDEX_BUFFER_VIEW* IndexBuffer::GetibViewAddress()
{
	return &ibView;
}
