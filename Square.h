#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "ViewProjection.h"

#include <DirectXMath.h>
using namespace DirectX;

class Square
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	TextureBuffer* textureBuffer;
	ConstantBuffer* constantBuffer;

	Transform* transform;
	ViewProjection* viewProjection;

private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数
public:
	Square();
	~Square();
	void Initialize();
	void DrawBox(XMFLOAT3 pos, XMFLOAT4 color);
	void DrawGraph();
public:
	VertexBuffer* GetVertexBuffer();
	TextureBuffer* GetTextureBuffer();
};