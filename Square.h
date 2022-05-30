#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "MathUtil.h"

#include <d3d12.h>

class Square
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	TextureBuffer* textureBuffer;
	ConstantBuffer* constantBuffer;
	Transform transform;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;

	Vec2 size;

	// 頂点データ
	Vertex vertices[4];
private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数

	int viewType;
public:
	Square();
	~Square();
	void SetTexture(const Texture& texture);
	void Initialize(int viewType, Vec2 size = { 0,0 });
	void Update(const Transform& transform, Transform* parent = nullptr);
	void Draw();
public:
	VertexBuffer* GetVertexBuffer();
	TextureBuffer* GetTextureBuffer();
	void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle);

	void SetColor(const Vec4& color);

	void SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize);
public:
	enum ViewType
	{
		view2D,
		view3D,
	};
};