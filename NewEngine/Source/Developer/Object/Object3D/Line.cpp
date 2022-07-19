#include "NewEngine/Header/Developer/Object/Object3D/Line.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/ComponentManager.h"
#include "NewEngine/Header/Render/RenderBase.h"

Line::Line() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
	objectType = ObjectType::LineType;
}

Line::~Line()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Line::Initialize(const Vec3& startPos, const Vec3& endPos)
{
	Texture* tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>()->SetTexture(tmpTex);
	delete tmpTex;

	vertices.push_back({ startPos,{}, {0.0f, 1.0f} });	//左下
	vertices.push_back({ endPos,  {}, {0.0f, 1.0f} });	//左下

	indices.push_back(0);
	indices.push_back(1);

	vertexBuffer->Initialize(vertices);
	indexBuffer->Initialize(indices);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();
}

void Line::Update()
{
	GetComponent<Transform>()->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->worldMat *
		view->matView *
		view->matProjection3D;

	constantBuffer->SetColor(this->color);
}

void Line::Draw()
{
	GetComponent<Blend>()->SetBlendMode(BlendMode::AddLine);

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

	renderBase->GetCommandList()->DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}
