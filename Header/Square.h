#pragma once
#include "Header/VertexBuffer.h"
#include "Header/IndexBuffer.h"
#include "Header/TextureBuffer.h"
#include "Header/ConstantBuffer.h"
#include "Header/Transform.h"
#include "Header/MathUtil.h"
#include "NewEngine/Header/Developer/Util/Util.h"

class Square
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Texture texture;
	Transform transform;
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