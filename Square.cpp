#include "Square.h"
#include "NewEngineBase.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),

	ibArraySize(0), vbArraySize(0), viewType(view3D)
{
}

Square::~Square()
{
	//vertexBuffer->Unmap();

	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Square::Initialize(int viewType, Vec2 size)
{
	this->viewType = viewType;
	this->size = size;

	// ���_�f�[�^
	if (viewType == view2D)
	{
		vertices[0] = { { -(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {0.0f, 1.0f} }; //����
		vertices[1] = { { -(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {0.0f, 0.0f} }; //����
		vertices[2] = { { +(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {1.0f, 1.0f} }; //�E��
		vertices[3] = { { +(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {1.0f, 0.0f} }; //�E��
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

	texture = TextureBuffer::GetDefaultTexture();
}

void Square::Update(const Transform& transform, Transform* parent)
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

void Square::Draw()
{
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
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Square::SetTexture(const Texture& texture)
{
	this->texture = texture;
}

void Square::SetColor(const Color& color)
{
	// �F�̎w��
	constantBuffer->SetColor(color);
}

void Square::SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize)
{
	float texLeft = cutPos.x / texture.GetTextureSize().x;
	float texRight = (cutPos.x + cutSize.x) / texture.GetTextureSize().x;
	float texUp = cutPos.y / texture.GetTextureSize().y;
	float texDown = (cutPos.y + cutSize.y) / texture.GetTextureSize().y;

	vertices[0].uv = { texLeft , texDown };	// ����
	vertices[1].uv = { texLeft ,   texUp };	// ����
	vertices[2].uv = { texRight ,texDown }; // �E��
	vertices[3].uv = { texRight ,  texUp }; // �E��

	vertexBuffer->TransferToBuffer();
}