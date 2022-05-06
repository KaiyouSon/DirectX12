#include "Square.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"
#include "GraphicsPipeline.h"

#include <d3d12.h>

extern NewEngineBase* newEngine;
extern NewEngineWindow* newEngineWin;
extern ShaderResourceView* shaderResourceView;
extern GraphicsPipeline* graphicsPipeline;
extern ViewProjection* view;

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer),

	transform(new Transform)
{
}

Square::~Square()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
}

void Square::Initialize()
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

	// �e�N�X�`���[�o�b�t�@
	textureBuffer->Initialize1();

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	// ���s���e�s��̌v�Z
	constantBuffer->constMapTransform->mat = XMMatrixOrthographicOffCenterLH(
		0, newEngineWin->GetWinWidth(),
		newEngineWin->GetWinHeight(), 0,
		0, 1);
}

void Square::DrawBox(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT4 color)
{
	transform->pos = pos;
	transform->scale = scale;

	transform->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		transform->matWorld * view->matView * view->matProjection;

	// �F�̎w��
	textureBuffer->SetImageDate(
		XMFLOAT4(color.x / 255, color.y / 255, color.z / 255, color.w / 255));

	////---------- �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h ----------//
	//// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	//newEngine->GetCommandList()->SetPipelineState(
	//	graphicsPipeline->GetPipelineState());
	//newEngine->GetCommandList()->SetGraphicsRootSignature(
	//	graphicsPipeline->GetRootSignature());

	//// SRV�q�[�v�̐ݒ�R�}���h
	//newEngine->GetCommandList()->SetDescriptorHeaps(
	//	1, shaderResourceView->GetsrvHeapAddress());
	//// SRV�q�[�v�̐擪�n���h�����擾
	//D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle =
	//	shaderResourceView->GetsrvHeap()->GetGPUDescriptorHandleForHeapStart();
	//// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	//newEngine->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

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

void Square::DrawGraph()
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

TextureBuffer* Square::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Square::GetVertexBuffer()
{
	return  vertexBuffer;
}