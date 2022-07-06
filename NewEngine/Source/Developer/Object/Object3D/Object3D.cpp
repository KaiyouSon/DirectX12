#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Render/RenderBase.h"
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

	Texture tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(&tmpTex);
}

void Object3D::Update()
{
	GetComponent<Transform>()->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->matWorld *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Object3D::Draw()
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			RenderBase::GetInstance()->GetSrvDescHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootDescriptorTable(1,
			GetComponent<Texture>()->GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	RenderBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced((unsigned short)this->modelData.indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}
void Object3D::SetColor(Color& color)
{
	this->color = color;

}
