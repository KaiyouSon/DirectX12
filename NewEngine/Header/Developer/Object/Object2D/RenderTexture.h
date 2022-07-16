#pragma once
#include "NewEngine/Header/Render/Buffer/VertexBuffer.h"
#include "NewEngine/Header/Render/Buffer/IndexBuffer.h"
#include "NewEngine/Header/Render/Buffer/ConstantBuffer.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Developer/Object/Other/GameObject.h"
#include <vector>
#include <d3dx12.h>
#include <wrl.h>

class RenderTexture : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

	Vec2 size;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static const float clearColor[4];
public:
	RenderTexture();
	~RenderTexture();
	void SetTexture(const Texture& texture);
	void Initialize(Vec2 size);
	void Update();

	void PreDrawScene();
	void PostDrawScene();
	void Draw();
public:
	void SetColor(const Color& color);
	void SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize);

	Texture GetRenderTexture();
};