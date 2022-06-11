#include "Cube.h"
#include "NewEngineBase.h"
#include "TextureBuffer.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"

#include <d3d12.h>

Cube::Cube() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),
	vbArraySize(0), ibArraySize(0)
{
}

Cube::~Cube()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Cube::SetTexture(const Texture& texture)
{
	this->texture = texture;
}

void Cube::Initialize()
{
	// 頂点データ
	Vertex vertices[] =
	{
		// 前
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //左下
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //左上
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //右下
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //右上

		// 後
		{ { +2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //左下
		{ { +2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //左上
		{ { -2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //右下
		{ { -2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //右上

		// 左
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //左下
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //左上
		{ { -2.5f, -2.5f, -2.5f },{},{1.0f, 1.0f} }, //右下
		{ { -2.5f, +2.5f, -2.5f },{},{1.0f, 0.0f} }, //右上

		// 右
		{ { +2.5f, -2.5f, -2.5f },{},{0.0f, 1.0f} }, //左下
		{ { +2.5f, +2.5f, -2.5f },{},{0.0f, 0.0f} }, //左上
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //右下
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //右上

		// 上
		{ { -2.5f, +2.5f, -2.5f },{},{0.0f, 1.0f} }, //左下
		{ { -2.5f, +2.5f, +2.5f },{},{0.0f, 0.0f} }, //左上
		{ { +2.5f, +2.5f, -2.5f },{},{1.0f, 1.0f} }, //右下
		{ { +2.5f, +2.5f, +2.5f },{},{1.0f, 0.0f} }, //右上

		// 下
		{ { -2.5f, -2.5f, +2.5f },{},{0.0f, 1.0f} }, //左下
		{ { -2.5f, -2.5f, -2.5f },{},{0.0f, 0.0f} }, //左上
		{ { +2.5f, -2.5f, +2.5f },{},{1.0f, 1.0f} }, //右下
		{ { +2.5f, -2.5f, -2.5f },{},{1.0f, 0.0f} }, //右上
	};

	// インデックスデータ
	uint16_t indices[] =
	{
		// 前		// 後
		0,1,2, 		4,5,6,
		2,1,3, 		6,5,7,

		// 左		// 右
		8,9,10,		12,13,14,
		10,9,11,	14,13,15,

		// 上	   	// 下
		16,17,18,	20,21,22,
		18,17,19,	22,21,23,
	};

	// 頂点データの要素数
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// インデックスの要素数
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// 三角形一つごとに計算していく
	for (int i = 0; i < ibArraySize / 3; i++)
	{
		// 三角形のインデックスを取り出して、一時的な変数に入れつ
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];

		// 三角形を構成する頂点座標をベクトルに代入
		Vec3 p0(
			vertices[index0].pos.x,
			vertices[index0].pos.y,
			vertices[index0].pos.z);
		Vec3 p1(
			vertices[index1].pos.x,
			vertices[index1].pos.y,
			vertices[index1].pos.z);
		Vec3 p2(
			vertices[index2].pos.x,
			vertices[index2].pos.y,
			vertices[index2].pos.z);

		// ベクトルの減算
		Vec3 v1 = p1 - p0;
		Vec3 v2 = p2 - p0;

		// 外積は両方から垂直なベクトル
		Vec3 normal = Vec3::Cross(v1, v2);

		// 求めた法線を各頂点データに代入
		vertices[index0].normal = normal.Normalized();
		vertices[index1].normal = normal.Normalized();
		vertices[index2].normal = normal.Normalized();
	}

	// 頂点バッファ
	vertexBuffer->Initialize(vertices, vbArraySize);
	// インデックスバッファ
	indexBuffer->Initialize(indices, ibArraySize);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Cube::Update(const Transform& transform, Transform* parent)
{
	this->transform = transform;

	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		view->matView *
		view->matProjection3D;
}

void Cube::Draw()
{
	// プリミティブ形状の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			ShaderResourceView::GetInstance()->GetSrvHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootDescriptorTable(1, texture.GetGpuHandle());

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	NewEngineBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Cube::SetColor(const Color& color)
{
	// 色の指定
	constantBuffer->SetColor(color);
}