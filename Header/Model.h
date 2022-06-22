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
	// 頂点データ配列
	static std::vector<Vertex> vertices;
	// 頂点インデックス配列
	static std::vector<unsigned short> indices;

public:
	Model();
	~Model();
	void Load();
	void Update(Transform& transform, Transform* parent = nullptr);
	void Draw();

};

