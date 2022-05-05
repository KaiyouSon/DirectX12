#include "Sprite.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "TextureBuffer.h"
#include "NewEngineBase.h"

#include <d3d12.h>

extern NewEngineBase* newEngine;
extern VertexBuffer* vertexBuffer;
extern IndexBuffer* indexBuffer;
extern TextureBuffer* textureBuffer;
extern ConstantBuffer* constantBuffer;

Sprite::Sprite()
{
}

void Sprite::Initialize()
{
	HRESULT result;

	// ���_�f�[�^
	Vertex vertices[] = {
	 { { -50.0f, -50.0f, 100.0f }, {0.0f, 1.0f} }, //����
	 { { -50.0f, +50.0f, 100.0f }, {0.0f, 0.0f} }, //����
	 { { +50.0f, -50.0f, 100.0f }, {1.0f, 1.0f} }, //�E��
	 { { +50.0f, +50.0f, 100.0f }, {1.0f, 0.0f} }, //�E��
	};
	// ���_�f�[�^�̗v�f��
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);

	// ���_�o�b�t�@
	vertexBuffer->Initialize(vertices, vbArraySize);

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		0,1,2, // �O�p�`1��
		1,2,3, // �O�p�`2��
	};
	//�C���f�b�N�X�̗v�f��
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(indices, ibArraySize);
}

void Sprite::DrawBox(XMFLOAT4 color)
{
	// �F�̎w��
	textureBuffer->SetImageDate(
		XMFLOAT4(color.x / 255, color.y / 255, color.z / 255, color.w / 255));

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	newEngine->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	newEngine->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	newEngine->GetCommandList()->DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Sprite::DrawGraph()
{
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	newEngine->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	newEngine->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	newEngine->GetCommandList()->DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}