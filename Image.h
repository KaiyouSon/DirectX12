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
	int vbArraySize;	// ���_�f�[�^�̗v�f��
	int ibArraySize;	// �C���f�b�N�X�f�[�^�̗v�f��
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