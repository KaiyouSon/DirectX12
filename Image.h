#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "ConstantBuffer.h"
#include "Transform.h"

#include <DirectXMath.h>
using namespace DirectX;

class Image
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	TextureBuffer* textureBuffer;
	ConstantBuffer* constantBuffer;

	Transform* transform;

private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数
	wchar_t* szFire;
public:
	Image();
	~Image();
	void Initialize(const wchar_t* szFile);
	void Update(XMFLOAT3 pos, XMFLOAT3 scale);
	void Draw();
public:
	VertexBuffer* GetVertexBuffer();
	TextureBuffer* GetTextureBuffer();
};