#include "NewEngine/Header/Developer/Object/Object2D/Sprite.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Render/RenderBase.h"

Sprite::Sprite() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer), layer(true)
{
}

Sprite::~Sprite()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Sprite::Initialize()
{
	Texture tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(&tmpTex);

	float width = tmpTex.GetTextureSize().x;
	float height = tmpTex.GetTextureSize().x;

	vertices.push_back({ { -(width / 2), +(height / 2), 0.0f },{}, {0.0f, 1.0f} });	//����
	vertices.push_back({ { -(width / 2), -(height / 2), 0.0f },{}, {0.0f, 0.0f} });	//����
	vertices.push_back({ { +(width / 2), +(height / 2), 0.0f },{}, {1.0f, 1.0f} });	//�E��
	vertices.push_back({ { +(width / 2), -(height / 2), 0.0f },{}, {1.0f, 0.0f} });	//�E��

	// �O�p�`1��
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	// �O�p�`2��
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	vertexBuffer->Initialize(vertices);
	indexBuffer->Initialize(indices);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();
}

void Sprite::Update()
{
	GetComponent<Transform>()->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->matWorld *
		view->matProjection2D;

	float width = GetComponent<Texture>()->GetTextureSize().x;
	float height = GetComponent<Texture>()->GetTextureSize().y;

	if (width / 2 != MathUtil::Absolut(vertices.at(0).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(0).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(1).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(1).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(2).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(2).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(3).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(3).pos.y))
	{
		vertices.at(0).pos = { -(width / 2), +(height / 2), 0.0f };	// ����
		vertices.at(1).pos = { -(width / 2), -(height / 2), 0.0f };	// ����
		vertices.at(2).pos = { +(width / 2), +(height / 2), 0.0f }; // �E��
		vertices.at(3).pos = { +(width / 2), -(height / 2), 0.0f }; // �E��

		vertexBuffer->TransferToBuffer(vertices);
		vertexBuffer->Unmap();
	}

	constantBuffer->SetColor(color);
}

void Sprite::Draw()
{
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

bool Sprite::GetLayer()
{
	return layer;
}

void Sprite::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

void Sprite::SetLayer(bool layer)
{
	this->layer = layer;
}

Mat4 Sprite::GetFinalMat()
{
	return constantBuffer->constMapTransform->mat;
}