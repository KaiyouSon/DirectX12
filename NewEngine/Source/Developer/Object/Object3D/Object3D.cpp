#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Render/RenderBase.h"
using namespace std;

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

	Texture tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(&tmpTex);
}

void Object3D::Update()
{
	GetComponent<Transform>()->Update();

	//color = { 255,0,255,255 };

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->matWorld *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Object3D::Draw()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	// 頂点バッファビューの設定コマンド
	renderBase->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	renderBase->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	renderBase->GetCommandList()->
		SetDescriptorHeaps(1,
			renderBase->GetSrvDescHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	renderBase->GetCommandList()->
		SetGraphicsRootDescriptorTable(1,
			GetComponent<Texture>()->GetGpuHandle());

	// 定数バッファビュー(CBV)の設定コマンド
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	renderBase->GetCommandList()->
		DrawIndexedInstanced((unsigned short)GetComponent<ModelData>()->indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(Texture& texture)
{
	GetComponent<Texture>()->SetTexture(&texture);
}

Mat4 Object3D::GetFinalMat()
{
	return constantBuffer->constMapTransform->mat;
}
