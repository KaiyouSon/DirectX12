#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "Vec2.h"

#include <d3d12.h>

class Cube
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Texture texture;
	Transform transform;

private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数

	int viewType;
public:
	Cube();
	~Cube();
	void SetTexture(const Texture& texture);
	void Initialize();
	void Update(const Transform& transform, Transform* parent = nullptr);
	void Draw();
public:
	void SetColor(const Vec4& color);
};
