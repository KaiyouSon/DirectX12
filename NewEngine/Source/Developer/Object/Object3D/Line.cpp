#include "NewEngine/Header/Developer/Object/Object3D/Line.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Render/RenderBase.h"

Line::Line() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
	objectType = ObjectType::LineType;
}

Line::~Line()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Line::Initialize(const Vec3& startPos, const Vec3& endPos)
{
	Texture* tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(tmpTex);
	delete tmpTex;

	vertices.push_back({ startPos,{}, {0.0f, 1.0f} });	//����
	vertices.push_back({ endPos,  {}, {0.0f, 1.0f} });	//����

	indices.push_back(0);
	indices.push_back(1);

	vertexBuffer->Initialize(vertices);
	indexBuffer->Initialize(indices);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();
}

void Line::Update()
{
	GetComponent<Transform>()->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->worldMat *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Line::Draw()
{
	GetComponent<Blend>()->SetBlendMode(BlendMode::AddLine);

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

	renderBase->GetCommandList()->DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}
