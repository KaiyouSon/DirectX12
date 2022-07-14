#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Component/ModelData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

Texture* LoadTexture(const char* filePath)
{
	return TextureBuffer::LoadTexture(filePath);
}

ModelData LoadModel(const char* filePath)
{
	// �t�@�C���X�g���[��
	ifstream file;
	// .obj�t�@�C�����J��
	file.open(filePath);
	// �t�@�C���I�[�v�����s���`�F�b�N
	//if (file.fail()) assert(0);
	if (file.fail())
	{
		ModelData errorModel;
		errorModel.SetTag("error");
		return errorModel;
	}

	ModelData modelData;
	vector<Vec3> positions;
	vector<Vec3> normals;
	vector<Vec2> texcoords;

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
		}

		// �擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			// uv�����ǂݍ���
			Vec2 texcoord{};
			lineStream >> texcoord.x;
			lineStream >> texcoord.y;
			// v�������]
			texcoord.y = 1.0f - texcoord.y;
			// �e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}

		// �擪������vn�Ȃ�@���x�N�g��
		if (key == "vn")
		{
			// xyz�����ǂݍ���
			Vec3 normal{};
			lineStream >> normal.x;
			lineStream >> normal.y;
			lineStream >> normal.z;
			// �@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal);
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
				unsigned short indexPos, indexNormal, indexTexcoord;
				indexStream >> indexPos;
				indexStream.seekg(1, ios_base::cur);	// �X���b�V�����΂�
				indexStream >> indexTexcoord;
				indexStream.seekg(1, ios_base::cur);	// �X���b�V�����΂�
				indexStream >> indexNormal;
				// ���_�f�[�^�̒ǉ�
				Vertex vertex{};
				vertex.pos = positions[indexPos - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				modelData.vertices.emplace_back(vertex);

				// ���_�C���f�b�N�X�ɒǉ�
				modelData.indices.emplace_back((unsigned short)modelData.indices.size());
			}
		}
	}

	// �t�@�C�������
	file.close();

	// �t�@�C���p�X
	modelData.SetFilePath(filePath);

	return modelData;
}
void UnLoadTexture(Texture* texture)
{
	TextureBuffer::UnLoadTexture(texture);
}