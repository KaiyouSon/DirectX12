#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Component/Transform.h"

class Square
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Texture texture;
	Transform transform;
	Vec2 size;
	// ���_�f�[�^
	Vertex vertices[4];
private:
	int vbArraySize;	// ���_�f�[�^�̗v�f��
	int ibArraySize;	// �C���f�b�N�X�f�[�^�̗v�f��

	int viewType;
public:
	Square();
	~Square();
	void SetTexture(const Texture& texture);
	void Initialize(int viewType, Vec2 size);
	void Update(const Transform& transform, Transform* parent = nullptr);
	void Draw();
public:
	void SetColor(const Color& color);
	void SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize);
public:
	enum ViewType
	{
		view2D,
		view3D,
	};
};