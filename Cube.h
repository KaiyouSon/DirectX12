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
	TextureBuffer* textureBuffer;
	ConstantBuffer* constantBuffer;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	Transform transform;

	Vec2 size;
private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数
	wchar_t* szFire;

	int viewType;
public:
	Cube();
	~Cube();
	void SetTexture(const Texture& texture);
	void Initialize();
	void Update(const Transform& transform, Transform* parent = nullptr);
	void Draw();
public:
	VertexBuffer* GetVertexBuffer();
	TextureBuffer* GetTextureBuffer();
	void SetGpuHandle(const D3D12_GPU_DESCRIPTOR_HANDLE& srvGpuHandle);

	void SetColor(const Vec4& color);
};
