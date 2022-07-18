#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include <vector>

class Sprite : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	bool layer;

public:
	Sprite();
	~Sprite();
	void Initialize();
	void Update();
	void Draw();

	bool GetLayer();
	Mat4 GetFinalMat();

	void SetLayer(bool layer);
};

