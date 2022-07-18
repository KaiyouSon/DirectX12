#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Render/RenderBase.h"

Object3D::Object3D() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Object3D::~Object3D()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Object3D::Initialize(const ModelData& modelData)
{
	GetComponent<ModelData>()->SetModelData(modelData);

	// 頂点バッファ
	vertexBuffer->Initialize(GetComponent<ModelData>()->vertices);
	// インデックスバッファ
	indexBuffer->Initialize(GetComponent<ModelData>()->indices);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	Texture* tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(tmpTex);
	delete tmpTex;
}

void Object3D::Update()
{
	GetComponent<Transform>()->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->worldMat *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Object3D::Draw()
{
	GetComponent<Blend>()->SetBlendMode(BlendMode::Alpha3D);

	// VBVとIBVの設定コマンド
	renderBase->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	renderBase->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// マテリアルとトランスフォームのCBVの設定コマンド
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		1, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	renderBase->GetCommandList()->SetDescriptorHeaps(1, renderBase->GetSrvDescHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ2番に設定
	renderBase->GetCommandList()->SetGraphicsRootDescriptorTable(2, GetComponent<Texture>()->GetGpuHandle());

	renderBase->GetCommandList()->DrawIndexedInstanced((unsigned short)GetComponent<ModelData>()->indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

Mat4 Object3D::GetFinalMat()
{
	return constantBuffer->constMapTransform->mat;
}
