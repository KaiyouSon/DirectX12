#include "Square.h"
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

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	textureBuffer(new TextureBuffer),
	constantBuffer(new ConstantBuffer),

	transform(new Transform)
{
}

Square::~Square()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete textureBuffer;
	delete constantBuffer;
}

void Square::Initialize()
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

	// テクスチャーバッファ
	textureBuffer->Initialize1();

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	// 並行投影行列の計算
	constantBuffer->constMapTransform->mat = XMMatrixOrthographicOffCenterLH(
		0, newEngineWin->GetWinWidth(),
		newEngineWin->GetWinHeight(), 0,
		0, 1);
}

void Square::DrawBox(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT4 color)
{
	transform->pos = pos;
	transform->scale = scale;

	transform->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		transform->matWorld * view->matView * view->matProjection;

	// 色の指定
	textureBuffer->SetImageDate(
		XMFLOAT4(color.x / 255, color.y / 255, color.z / 255, color.w / 255));

	////---------- パイプラインステートとルートシグネチャの設定コマンド ----------//
	//// パイプラインステートとルートシグネチャの設定コマンド
	//newEngine->GetCommandList()->SetPipelineState(
	//	graphicsPipeline->GetPipelineState());
	//newEngine->GetCommandList()->SetGraphicsRootSignature(
	//	graphicsPipeline->GetRootSignature());

	//// SRVヒープの設定コマンド
	//newEngine->GetCommandList()->SetDescriptorHeaps(
	//	1, shaderResourceView->GetsrvHeapAddress());
	//// SRVヒープの先頭ハンドルを取得
	//D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle =
	//	shaderResourceView->GetsrvHeap()->GetGPUDescriptorHandleForHeapStart();
	//// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	//newEngine->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

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

void Square::DrawGraph()
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

TextureBuffer* Square::GetTextureBuffer()
{
	return textureBuffer;
}

VertexBuffer* Square::GetVertexBuffer()
{
	return  vertexBuffer;
}