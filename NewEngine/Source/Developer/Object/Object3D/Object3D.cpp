#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "Header/Vertex.h"
#include "NewEngine/Render/Header/NewEngineBase.h"
#include "Header/ShaderResourceView.h"
#include "Header/ViewProjection.h"
#include "Header/MathUtil.h"
using namespace std;

Object3D::Object3D() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Object3D::~Object3D()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Object3D::Initialize(const ModelData& modelData)
{
	this->modelData = modelData;

	// ���_�o�b�t�@
	vertexBuffer->Initialize(this->modelData.vertices);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(this->modelData.indices);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Object3D::Update(Transform& transform, Transform* parent)
{
	this->transform = transform;
	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		view->matView *
		view->matProjection3D;
}

void Object3D::Update()
{
	this->transform.Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		view->matView *
		view->matProjection3D;
}

void Object3D::Draw()
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			ShaderResourceView::GetInstance()->GetSrvHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootDescriptorTable(1, texture.GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	NewEngineBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced((unsigned short)this->modelData.indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(const Texture& texture)
{
	this->texture = texture;
}