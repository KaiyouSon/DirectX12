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
private:
	int vbArraySize;	// ���_�f�[�^�̗v�f��
	int ibArraySize;	// �C���f�b�N�X�f�[�^�̗v�f��
	wchar_t* szFire;

	int viewType;
public:
	Square();
	Square(Vec2 size);
	~Square();
	void LoadGraph(const wchar_t* FilePath);
	void SetTexture(const Texture& texture);
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