#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include <d3dx12.h>
#include <wrl.h>

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

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static const float clearColor[4];

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

	void PreDrawScene();
	void PostDrawScene();
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