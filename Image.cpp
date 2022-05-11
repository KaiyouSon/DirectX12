#include "Image.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"
#include "GraphicsPipeline.h"

#include <d3d12.h>

extern NewEngineBase* newEngine;
extern NewEngineWindow* newEngineWin;
extern ShaderResourceView* shaderResourceView;
extern GraphicsPipeline* graphicsPipeline;
extern ViewProjection* view;

Image::Image() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer),
	transform(new Transform)
{
}

Image::~Image()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
	delete transform;
}

void Image::Initialize(const wchar_t* szFile)
{
	HRESULT result;

	// 頂点データ
	Vertex vertices[] =
	{
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

	// テクスチャーバッファ
	textureBuffer->Initialize2(szFile);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	// 並行投影行列の計算
	constantBuffer->constMapTransform->mat = XMMatrixOrthographicOffCenterLH(
		0, newEngineWin->GetWinWidth(),
		newEngineWin->GetWinHeight(), 0,
		0, 1);
}

void Image::Update(XMFLOAT3 pos, XMFLOAT3 scale)
{
	transform->pos = pos;
	transform->scale = scale;

	transform->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		transform->matWorld * view->matView * view->matProjection;
}

void Image::Draw()
{
	// 頂点バッファビューの設定コマンド
	newEngine->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	newEngine->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	newEngine->GetCommandList()->SetDescriptorHeaps(
		1, shaderResourceView->GetsrvHeapAddress());
	// SRVヒープの先頭ハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle =
		shaderResourceView->GetSrvGpuHandle();
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	newEngine->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

	// 定数バッファビュー(CBV)の設定コマンド
	newEngine->GetCommandList()->SetGraphicsRootConstantBufferView(
		2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	newEngine->GetCommandList()->DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

TextureBuffer* Image::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Image::GetVertexBuffer()
{
	return  vertexBuffer;
}