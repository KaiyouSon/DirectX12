#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include "NewEngine/Header/Developer/Component/ModelData.h"

class Object3D : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

public:
	Object3D();
	~Object3D();
	void Initialize(const ModelData& modelData);
	void Update();
	void Draw();

	void SetTexture(Texture& texture);
	void SetColor(Color& color);

	Mat4 GetFinalMat();
};

