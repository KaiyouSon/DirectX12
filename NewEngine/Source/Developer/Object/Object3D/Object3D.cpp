#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Render/RenderBase.h"

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

	Texture* tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(tmpTex);
	delete tmpTex;
}

void Object3D::Update()
{
	GetComponent<Transform>()->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->worldMat *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Object3D::Draw()
{
	GetComponent<Blend>()->SetBlendMode(BlendMode::Alpha3D);

	// VBV��IBV�̐ݒ�R�}���h
	renderBase->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	renderBase->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �}�e���A���ƃg�����X�t�H�[����CBV�̐ݒ�R�}���h
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		1, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	renderBase->GetCommandList()->SetDescriptorHeaps(1, renderBase->GetSrvDescHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^2�Ԃɐݒ�
	renderBase->GetCommandList()->SetGraphicsRootDescriptorTable(2, GetComponent<Texture>()->GetGpuHandle());

	renderBase->GetCommandList()->DrawIndexedInstanced((unsigned short)GetComponent<ModelData>()->indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

Mat4 Object3D::GetFinalMat()
{
	return constantBuffer->constMapTransform->mat;
}
