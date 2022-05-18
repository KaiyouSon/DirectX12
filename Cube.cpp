#include "Cube.h"
#include "NewEngineBase.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"

#include <d3d12.h>

Cube::Cube() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Cube::~Cube()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
}

void Cube::LoadGraph(const wchar_t* FilePath)
{
	// �e�N�X�`���[�o�b�t�@
	textureBuffer->Initialize2(FilePath);
}

void Cube::Initialize()
{
	this->viewType = viewType;

	// ���_�f�[�^
	Vertex vertices[] =
	{
		// �O
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��

		// �w
		{ { +2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { +2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { -2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { -2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { -2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { -2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��

		// �E
		{ { +2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { +2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		// �O
		0,1,2, // �O�p�`1��
		2,1,3, // �O�p�`2��

		// �w
		4,5,6,
		6,5,7,

		// ��
		8,9,10,
		10,9,11,

		// �E
		12,13,14,
		14,13,15,

		// ��
		16,17,18,
		18,17,19,

		// ��
		20,21,22,
		22,21,23,
	};

	// ���_�f�[�^�̗v�f��
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// �C���f�b�N�X�̗v�f��
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// �O�p�`����ƂɌv�Z���Ă���
	for (int i = 0; i < ibArraySize / 3; i++)
	{
		// �O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];

		// �O�p�`���\�����钸�_���W���x�N�g���ɑ��
		Vec3 p0(
			vertices[index0].pos.x,
			vertices[index0].pos.y,
			vertices[index0].pos.z);
		Vec3 p1(
			vertices[index1].pos.x,
			vertices[index1].pos.y,
			vertices[index1].pos.z);
		Vec3 p2(
			vertices[index2].pos.x,
			vertices[index2].pos.y,
			vertices[index2].pos.z);
		
		// �x�N�g���̌��Z
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;

		// �O�ς͗������琂���ȃx�N�g��
		Vec3 normal = Vec3::Cross(v1, v2);

		// ���߂��@�����e���_�f�[�^�ɑ��
		vertices[index0].normal = normal.Normalized();
		vertices[index1].normal = normal.Normalized();
		vertices[index2].normal = normal.Normalized();
	}

	// ���_�o�b�t�@
	vertexBuffer->Initialize(vertices, vbArraySize);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(indices, ibArraySize);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	// SRV�̍쐬
	ShaderResourceView::GetInstance().CreatSrv(*this);
}

void Cube::Update(const Transform& transform, Transform* parent)
{
	this->transform = transform;

	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	Mat4 tmpView = View::GetInstance().matView;
	Mat4 tmpProjection = View::GetInstance().matProjection3D;

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		tmpView *
		tmpProjection;
}

void Cube::Draw()
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		SetDescriptorHeaps(1, ShaderResourceView::GetInstance().GetsrvHeapAddress());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootDescriptorTable(1, srvGpuHandle);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	NewEngineBase::GetInstance().GetCommandList()->
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Cube::SetColor(const Vec4& color)
{
	// �F�̎w��
	constantBuffer->SetColor(color);
}

TextureBuffer* Cube::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Cube::GetVertexBuffer()
{
	return vertexBuffer;
}

void Cube::SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle)
{
	srvGpuHandle = _srvGpuHandle;
}