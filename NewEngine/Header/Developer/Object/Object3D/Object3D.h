#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include <vector>

struct ModelData
{
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
}typedef Model;

class Object3D : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
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

