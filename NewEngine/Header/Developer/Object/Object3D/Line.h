#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include <vector>

class Line : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

public:
	Line();
	~Line();
	void Initialize(const Vec3& startPos, const Vec3& endPos);
	void Update();
	void Draw();
};

