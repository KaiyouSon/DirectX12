#include "Sprite.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "TextureBuffer.h"
#include "NewEngineBase.h"

#include <d3d12.h>

extern NewEngineBase* newEngine;
extern VertexBuffer* vertexBuffer;
extern IndexBuffer* indexBuffer;
extern TextureBuffer* textureBuffer;
extern ConstantBuffer* constantBuffer;

Sprite::Sprite()
{
}

void Sprite::Initialize()
{
	HRESULT result;

	// 頂点データ
	Vertex vertices[] = {
	 { { -50.0f, -50.0f, 100.0f }, {0.0f, 1.0f} }, //左下
	 { { -50.0f, +50.0f, 100.0f }, {0.0f, 0.0f} }, //左上
	 { { +50.0f, -50.0f, 100.0f }, {1.0f, 1.0f} }, //右下
	 { { +50.0f, +50.0f, 100.0f }, {1.0f, 0.0f} }, //右上
	};
	// 頂点データの要素数
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);

	// 頂点バッファ
	vertexBuffer->Initialize(vertices, vbArraySize);

	// インデックスデータ
	uint16_t indices[] =
	{
		0,1,2, // 三角形1つ目
		1,2,3, // 三角形2つ目
	};
	//インデックスの要素数
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// インデックスバッファ
	indexBuffer->Initialize(indices, ibArraySize);
}

void Sprite::DrawBox(XMFLOAT4 color)
{
	// 色の指定
	textureBuffer->SetImageDate(
		XMFLOAT4(color.x / 255, color.y / 255, color.z / 255, color.w / 255));

	// 頂点バッファビューの設定コマンド
	newEngine->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	newEngine->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	newEngine->GetCommandList()->DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Sprite::DrawGraph()
{
	// 頂点バッファビューの設定コマンド
	newEngine->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	newEngine->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	newEngine->GetCommandList()->DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}