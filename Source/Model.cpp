#include "Header/Model.h"
#include "Header/Vertex.h"
#include "Header/NewEngineBase.h"
#include "Header/ShaderResourceView.h"
#include "Header/ViewProjection.h"
#include "Header/MathUtil.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

vector<Vertex> Model::vertices;
vector<unsigned short> Model::indices;

Model::Model() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Model::~Model()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Model::Load()
{
	// �t�@�C���X�g���[��
	ifstream file;
	// .obj�t�@�C�����J��
	file.open("NewEngine/BasicModel/Triangle.obj");
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) assert(0);

	vector<Vec3> positions;
	vector<Vec3> normals;
	vector<Vec3> texcoords;

	// 1�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');

		// �擪������v�Ȃ璸�_���W
		if (key == "v")
		{
			// X,Y,Z���W�ǂݍ���
			Vec3 pos{};
			lineStream >> pos.x;
			lineStream >> pos.y;
			lineStream >> pos.z;
			// ���W�f�[�^�ɒǉ�
			positions.emplace_back(pos);
			// ���_�f�[�^�ɒǉ�
			Vertex vertex{};
			vertex.pos = pos;
			vertices.emplace_back(vertex);
		}

		// �擪������f�Ȃ�|���S��(�O�p�`)
		if (key == "f")
		{
			// ���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string indexString;
			while (getline(lineStream, indexString, ' '))
			{
				// ���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				istringstream indexStream(indexString);
				unsigned short indexPos;
				indexStream >> indexPos;
				// ���_�C���f�b�N�X�ɒǉ�
				indices.emplace_back(indexPos - 1);
			}
		}
	}

	// ���_�o�b�t�@
	vertexBuffer->Initialize(vertices);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(indices);

	// �t�@�C�������
	file.close();

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Model::Update(Transform& transform, Transform* parent)
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
}

void Model::Draw()
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
		DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}
