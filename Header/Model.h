#pragma once
#include "Header/VertexBuffer.h"
#include "Header/IndexBuffer.h"
#include "Header/ConstantBuffer.h"
#include "Header/Transform.h"
#include "Header/TextureBuffer.h"
#include <vector>
class Model
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Transform transform;
	Texture texture;

public:
	// ���_�f�[�^�z��
	static std::vector<Vertex> vertices;
	// ���_�C���f�b�N�X�z��
	static std::vector<unsigned short> indices;

public:
	Model();
	~Model();
	void Load();
	void Update(Transform& transform, Transform* parent = nullptr);
	void Draw();

};

