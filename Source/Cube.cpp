#include "Header/Cube.h"
#include "Header/NewEngineBase.h"
#include "Header/TextureBuffer.h"
#include "Header/ViewProjection.h"
#include "Header/ShaderResourceView.h"
#include "Header/InputManager.h"
#include "Header/Util.h"
#include "ImGUI/imgui.h"
#include <d3d12.h>

Cube::Cube() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),
	vbArraySize(0), ibArraySize(0),
	isClick(false)
{
}

Cube::~Cube()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Cube::SetTexture(const Texture& texture)
{
	this->texture = texture;
}

void Cube::Initialize()
{
	// ���_�f�[�^
	Vertex vertices[] =
	{
		// �O
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { +2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { +2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { -2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { -2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { -2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { -2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��

		// �E
		{ { +2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { +2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //�E��

		// ��
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //����
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 0.0f} }, //����
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //�E��
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 0.0f} }, //�E��
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		// �O		// ��
		0,1,2, 		4,5,6,
		2,1,3, 		6,5,7,

		// ��		// �E
		8,9,10,		12,13,14,
		10,9,11,	14,13,15,

		// ��	   	// ��
		16,17,18,	20,21,22,
		18,17,19,	22,21,23,
	};

	// ���_�f�[�^�̗v�f��
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// �C���f�b�N�X�̗v�f��
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// �O�p�`����ƂɌv�Z���Ă���
	for (int i = 0; i < ibArraySize / 3; i++)
	{
		// �O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];

		// �O�p�`���\�����钸�_���W���x�N�g���ɑ��
		Vec3 p0(
			vertices[index0].pos.x,
			vertices[index0].pos.y,
			vertices[index0].pos.z);
		Vec3 p1(
			vertices[index1].pos.x,
			vertices[index1].pos.y,
			vertices[index1].pos.z);
		Vec3 p2(
			vertices[index2].pos.x,
			vertices[index2].pos.y,
			vertices[index2].pos.z);

		// �x�N�g���̌��Z
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;

		// �O�ς͗������琂���ȃx�N�g��
		Vec3 normal = Vec3::Cross(v1, v2);

		// ���߂��@�����e���_�f�[�^�ɑ��
		vertices[index0].normal = normal.Normalized();
		vertices[index1].normal = normal.Normalized();
		vertices[index2].normal = normal.Normalized();
	}

	// ���_�o�b�t�@
	vertexBuffer->Initialize(vertices, vbArraySize);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(indices, ibArraySize);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Cube::Update(Transform& transform, Transform* parent)
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

	InspectorWindow(transform);
}

void Cube::Draw()
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
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Cube::SetColor(const Color& color)
{
	this->color = color;
	// �F�̎w��
	constantBuffer->SetColor(this->color);
}

void Cube::InspectorWindow(Transform& transform)
{
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

	ImGui::SetNextWindowSize(ImVec2(480, WIN_HEIGHT));
	ImGui::SetNextWindowPos(ImVec2(WIN_WIDTH - 480, 0));
	ImGui::Begin("Inspector");

#pragma region Transform
	static float tmpPos[3] = { 0 };
	tmpPos[0] = transform.pos.x;
	tmpPos[1] = transform.pos.y;
	tmpPos[2] = transform.pos.z;
	static float tmpRot[3] = { 0 };
	tmpRot[0] = transform.rot.x;
	tmpRot[1] = transform.rot.y;
	tmpRot[2] = transform.rot.z;
	static float tmpScale[3] = { 0 };
	tmpScale[0] = transform.scale.x;
	tmpScale[1] = transform.scale.y;
	tmpScale[2] = transform.scale.z;
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Text("	x		  y		  z");
		ImGui::DragFloat3("Postion", tmpPos, 0.05);
		transform.pos.x = tmpPos[0];
		transform.pos.y = tmpPos[1];
		transform.pos.z = tmpPos[2];
		ImGui::DragFloat3("Rotation", tmpRot, 0.5);
		transform.rot.x = tmpRot[0];
		transform.rot.y = tmpRot[1];
		transform.rot.z = tmpRot[2];
		ImGui::DragFloat3("Scale", tmpScale, 0.05);
		transform.scale.x = tmpScale[0];
		transform.scale.y = tmpScale[1];
		transform.scale.z = tmpScale[2];

		this->transform = transform;
		this->transform.Update();
		// �萔�o�b�t�@�ɓ]��
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			view->matView *
			view->matProjection3D;
	}
#pragma endregion

#pragma region Color
	if (ImGui::CollapsingHeader("Color"))
	{
		static float tmpColor[4] =
		{
			color.r / 255,
			color.g / 255,
			color.b / 255,
			color.a / 255
		};
		ImGui::ColorEdit4("Color", tmpColor);
		color = Color::SetRGB(tmpColor[0] * 255, tmpColor[1] * 255, tmpColor[2] * 255);
		color.a = tmpColor[3] * 255;
		SetColor(color);
	}
#pragma endregion

	//ImGui::Text("MousePos = %f, %f", mouse->GetMousePos().x, mouse->GetMousePos().y);

	//ImGui::Text("matTrans = %f, %f, %f",
	//	transform.matTrans.mat[3][0], transform.matTrans.mat[3][1], transform.matTrans.mat[3][2]);

	//Mat4 tmp = this->transform.matWorld * view->matProjection2D;
	//ImGui::Text("MousePos = %f, %f", tmp.mat[3][0], tmp.mat[3][1], tmp.mat[3][2]);

	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}