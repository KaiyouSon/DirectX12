#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "Header/Vertex.h"
#include "NewEngine/Render/Header/NewEngineBase.h"
#include "Header/ShaderResourceView.h"
#include "Header/ViewProjection.h"
#include "Header/MathUtil.h"
using namespace std;

Object3D::Object3D() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
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
	this->modelData = modelData;

	// 頂点バッファ
	vertexBuffer->Initialize(this->modelData.vertices);
	// インデックスバッファ
	indexBuffer->Initialize(this->modelData.indices);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Object3D::Update(Transform& transform, Transform* parent)
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

void Object3D::Update()
{
	this->transform.Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		view->matView *
		view->matProjection3D;
}

void Object3D::Draw()
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
		DrawIndexedInstanced((unsigned short)this->modelData.indices.size(), 1, 0, 0, 0);
}

void Object3D::SetTexture(const Texture& texture)
{
	this->texture = texture;
}