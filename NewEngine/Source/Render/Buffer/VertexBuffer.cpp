#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include <cassert>

void VertexBuffer::Initialize(Vertex vertices[], int arrarySize)
{
	//this->vertices = vertices;
	this->arrarySize = arrarySize;

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * arrarySize);

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// ���_�o�b�t�@�̐���
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&heapProp, // �q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&resDesc, // ���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//----------------------- ���_�o�b�t�@�ւ̃f�[�^�]�� -----------------------//
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < arrarySize; i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}
	// �q���������
	//vertBuff->Unmap(0, nullptr);

	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	// ���_�P���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(vertices[0]);
}

void VertexBuffer::Initialize(std::vector<Vertex> vertices)
{
	arrarySize = vertices.size();

	//this->vertices = vertices;

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	unsigned int sizeVB = static_cast<unsigned int>(sizeof(Vertex) * vertices.size());

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	HRESULT result;

	// ���_�o�b�t�@�̐���
	result = RenderBase::GetInstance()->GetDevice()->
		CreateCommittedResource(
			&heapProp, // �q�[�v�ݒ�
			D3D12_HEAP_FLAG_NONE,
			&resDesc, // ���\�[�X�ݒ�
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//----------------------- ���_�o�b�t�@�ւ̃f�[�^�]�� -----------------------//
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	copy(vertices.begin(), vertices.end(), vertMap);

	//for (int i = 0; i < arrarySize; i++)
	//{
	//	vertMap[i] = vertices[i]; // ���W���R�s�[
	//}
	// �q���������
	vertBuff->Unmap(0, nullptr);

	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	// ���_�P���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(vertices[0]);

}

D3D12_VERTEX_BUFFER_VIEW* VertexBuffer::GetvbViewAddress()
{
	return &vbView;
}

void VertexBuffer::TransferToBuffer(std::vector<Vertex> vertices)
{
	HRESULT result;

	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂��ăR�s�[
	copy(vertices.begin(), vertices.end(), vertMap);

	//for (int i = 0; i < arrarySize; i++)
	//{
	//	vertMap[i] = vertices[i]; // ���W���R�s�[
	//}
}

void VertexBuffer::TransferToBuffer()
{
	HRESULT result;

	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂��ăR�s�[
	for (int i = 0; i < arrarySize; i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}
}

void VertexBuffer::Unmap()
{
	// �q���������
	vertBuff->Unmap(0, nullptr);
}
