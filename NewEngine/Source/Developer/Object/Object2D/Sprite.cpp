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
	GetComponent<Texture>("Texture")->SetTexture(&tmpTex);

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
	GetComponent<Transform>("Transform")->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>("Transform")->matWorld *
		view->matProjection2D;
}

void Sprite::Draw()
{
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
			GetComponent<Texture>("Texture")->GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	RenderBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}

bool Sprite::GetLayer()
{
	return layer;
}

void Sprite::SetTexture(Texture& texture)
{
	GetComponent<Texture>("Texture")->SetTexture(&texture);

	float width = texture.GetTextureSize().x;
	float height = texture.GetTextureSize().y;

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
}

void Sprite::SetLayer(bool layer)
{
	this->layer = layer;
}
