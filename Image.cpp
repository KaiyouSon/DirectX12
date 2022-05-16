#include "Image.h"
#include "NewEngineBase.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"
#include "GraphicsPipeline.h"

#include <d3d12.h>
#include <DirectXMath.h>
using namespace DirectX;

extern GraphicsPipeline* graphicsPipeline;

Image::Image() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Image::Image(Vec2 size) :
	size(size),
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Image::~Image()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
}

void Image::LoadGraph(const wchar_t* FilePath)
{
	// �e�N�X�`���[�o�b�t�@
	textureBuffer->Initialize2(FilePath);
}

void Image::Initialize(int viewType)
{
	this->viewType = viewType;

	// ���_�f�[�^
	Vertex vertices[4];
	if (viewType == view2D)
	{
		vertices[0] = { { -(size.x / 2), +(size.y / 2), 0.0f },{}, {0.0f, 1.0f} }; //����
		vertices[1] = { { -(size.x / 2), -(size.y / 2), 0.0f },{}, {0.0f, 0.0f} }; //����
		vertices[2] = { { +(size.x / 2), +(size.y / 2), 0.0f },{}, {1.0f, 1.0f} }; //�E��
		vertices[3] = { { +(size.x / 2), -(size.y / 2), 0.0f },{}, {1.0f, 0.0f} }; //�E��
	};
	if (viewType == view3D)
	{
		vertices[0] = { { -2.5f, -2.5f, 0.0f },{},{0.0f, 1.0f} }; //����
		vertices[1] = { { -2.5f, +2.5f, 0.0f },{},{0.0f, 0.0f} }; //����
		vertices[2] = { { +2.5f, -2.5f, 0.0f },{},{1.0f, 1.0f} }; //�E��
		vertices[3] = { { +2.5f, +2.5f, 0.0f },{},{1.0f, 0.0f} }; //�E��
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		0,1,2, // �O�p�`1��
		2,1,3, // �O�p�`2��
	};

	// ���_�f�[�^�̗v�f��
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// �C���f�b�N�X�̗v�f��
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

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

void Image::Update(const Transform& transform, Transform* parent)
{
	this->transform = transform;

	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// �萔�o�b�t�@�ɓ]��
	if (viewType == view2D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			View::GetInstance().matProjection2D;
	}
	if (viewType == view3D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			View::GetInstance().matView *
			View::GetInstance().matProjection3D;
	}
}

void Image::Draw()
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

void Image::SetColor(const Vec4& color)
{
	// �F�̎w��
	constantBuffer->SetColor(color);
}

TextureBuffer* Image::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Image::GetVertexBuffer()
{
	return  vertexBuffer;
}

void Image::SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle)
{
	srvGpuHandle = _srvGpuHandle;
}