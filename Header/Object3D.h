#pragma once
#include "Header/VertexBuffer.h"
#include "Header/IndexBuffer.h"
#include "Header/ConstantBuffer.h"
#include "Header/Transform.h"
#include "Header/TextureBuffer.h"
#include <vector>

struct ModelData
{
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
}typedef Model;

class Object3D
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Transform transform;
	Texture texture;
	ModelData modelData;

public:
	Object3D();
	~Object3D();
	void Initialize(const ModelData& modelData);
	void Update(Transform& transform, Transform* parent = nullptr);
	void Update();
	void Draw();

	void SetTexture(const Texture& texture);
};

