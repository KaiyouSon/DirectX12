#include "Image.h"
#include "NewEngineBase.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"
#include "GraphicsPipeline.h"

#include <d3d12.h>
#include <DirectXMath.h>
using namespace DirectX;

extern GraphicsPipeline* graphicsPipeline;

Image::Image() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Image::Image(Vec2 size) :
	size(size),
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Image::~Image()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
}

void Image::LoadGraph(const wchar_t* FilePath)
{
	// テクスチャーバッファ
	textureBuffer->Initialize2(FilePath);
}

void Image::Initialize(int viewType)
{
	this->viewType = viewType;

	// 頂点データ
	Vertex vertices[4];
	if (viewType == view2D)
	{
		vertices[0] = { { -(size.x / 2), +(size.y / 2), 0.0f },{}, {0.0f, 1.0f} }; //左下
		vertices[1] = { { -(size.x / 2), -(size.y / 2), 0.0f },{}, {0.0f, 0.0f} }; //左上
		vertices[2] = { { +(size.x / 2), +(size.y / 2), 0.0f },{}, {1.0f, 1.0f} }; //右下
		vertices[3] = { { +(size.x / 2), -(size.y / 2), 0.0f },{}, {1.0f, 0.0f} }; //右上
	};
	if (viewType == view3D)
	{
		vertices[0] = { { -2.5f, -2.5f, 0.0f },{},{0.0f, 1.0f} }; //左下
		vertices[1] = { { -2.5f, +2.5f, 0.0f },{},{0.0f, 0.0f} }; //左上
		vertices[2] = { { +2.5f, -2.5f, 0.0f },{},{1.0f, 1.0f} }; //右下
		vertices[3] = { { +2.5f, +2.5f, 0.0f },{},{1.0f, 0.0f} }; //右上
	};

	// インデックスデータ
	uint16_t indices[] =
	{
		0,1,2, // 三角形1つ目
		2,1,3, // 三角形2つ目
	};

	// 頂点データの要素数
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// インデックスの要素数
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// 頂点バッファ
	vertexBuffer->Initialize(vertices, vbArraySize);
	// インデックスバッファ
	indexBuffer->Initialize(indices, ibArraySize);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	// SRVの作成
	ShaderResourceView::GetInstance().CreatSrv(*this);
}

void Image::Update(const Transform& transform, Transform* parent)
{
	this->transform = transform;

	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// 定数バッファに転送
	if (viewType == view2D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			View::GetInstance().matProjection2D;
	}
	if (viewType == view3D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			View::GetInstance().matView *
			View::GetInstance().matProjection3D;
	}
}

void Image::Draw()
{
	// プリミティブ形状の設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		SetDescriptorHeaps(1, ShaderResourceView::GetInstance().GetsrvHeapAddress());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootDescriptorTable(1, srvGpuHandle);

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	NewEngineBase::GetInstance().GetCommandList()->
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Image::SetColor(const Vec4& color)
{
	// 色の指定
	constantBuffer->SetColor(color);
}

TextureBuffer* Image::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Image::GetVertexBuffer()
{
	return  vertexBuffer;
}

void Image::SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE _srvGpuHandle)
{
	srvGpuHandle = _srvGpuHandle;
}