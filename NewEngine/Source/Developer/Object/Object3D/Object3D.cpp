#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Render/RenderBase.h"
using namespace std;

Object3D::Object3D() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
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
	GetComponent<ModelData>()->SetModelData(modelData);

	// ���_�o�b�t�@
	vertexBuffer->Initialize(GetComponent<ModelData>()->vertices);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(GetComponent<ModelData>()->indices);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	Texture tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(&tmpTex);
}

void Object3D::Update()
{
	GetComponent<Transform>()->Update();

	//color = { 255,0,255,255 };

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->matWorld *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Object3D::Draw()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		SetDescriptorHeaps(1,
			renderBase->GetSrvDescHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	renderBase->GetCommandList()->
		SetGraphicsRootDescriptorTable(1,
			GetComponent<Texture>()->GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	renderBase->GetCommandList()->
		DrawIndexedInstanced((unsigned short)GetComponent<ModelData>()->indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

Mat4 Object3D::GetFinalMat()
{
	return constantBuffer->constMapTransform->mat;
}
