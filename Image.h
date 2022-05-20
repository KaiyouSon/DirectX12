#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "MathUtil.h"

#include <d3d12.h>

class Image
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	TextureBuffer* textureBuffer;
	ConstantBuffer* constantBuffer;
	Transform transform;
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;

	Vec2 size;
private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数
	wchar_t* szFire;

	int viewType;
public:
	Image();
	Image(Vec2 size);
	~Image();
	void LoadGraph(const wchar_t* FilePath = L"void");
	void Initialize(int viewType);
	void Update(const Transform& transform, Transform* parent = nullptr);
	void Draw();
public:
	VertexBuffer* GetVertexBuffer();
	TextureBuffer* GetTextureBuffer();
	void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle);

	void SetColor(const Vec4& color);
public:
	enum ViewType
	{
		view2D,
		view3D,
	};
};