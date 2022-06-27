#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include <d3d12.h>

class Cube
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Texture texture;
	Color color;

public:
	Transform transform;

private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数

private:
	bool isClick;
	void InspectorWindow(Transform& transform);

public:
	Cube();
	~Cube();
	void SetTexture(const Texture& texture);
	void Initialize();
	void Update(Transform& transform, Transform* parent = nullptr);
	void Draw();
	void SetColor(const Color& color);
};
