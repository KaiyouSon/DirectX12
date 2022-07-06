#include "NewEngine/Header/Developer/Object/Object2D/Sprite.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Render/RenderBase.h"

Sprite::Sprite() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer), layer(true)
{
}

Sprite::~Sprite()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Sprite::Initialize()
{
	Texture tmpTex = TextureBuffer::GetDefaultTexture();
	GetComponent<Texture>("Texture")->SetTexture(&tmpTex);

	float width = tmpTex.GetTextureSize().x;
	float height = tmpTex.GetTextureSize().x;

	vertices.push_back({ { -(width / 2), +(height / 2), 0.0f },{}, {0.0f, 1.0f} });	//左下
	vertices.push_back({ { -(width / 2), -(height / 2), 0.0f },{}, {0.0f, 0.0f} });	//左上
	vertices.push_back({ { +(width / 2), +(height / 2), 0.0f },{}, {1.0f, 1.0f} });	//右下
	vertices.push_back({ { +(width / 2), -(height / 2), 0.0f },{}, {1.0f, 0.0f} });	//右上

	// 三角形1つ目
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	// 三角形2つ目
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	vertexBuffer->Initialize(vertices);
	indexBuffer->Initialize(indices);

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();
}

void Sprite::Update()
{
	GetComponent<Transform>("Transform")->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>("Transform")->matWorld *
		view->matProjection2D;
}

void Sprite::Draw()
{
	// 頂点バッファビューの設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			RenderBase::GetInstance()->GetSrvDescHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootDescriptorTable(1,
			GetComponent<Texture>("Texture")->GetGpuHandle());

	// 定数バッファビュー(CBV)の設定コマンド
	RenderBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	RenderBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}

bool Sprite::GetLayer()
{
	return layer;
}

void Sprite::SetTexture(Texture& texture)
{
	GetComponent<Texture>("Texture")->SetTexture(&texture);

	float width = texture.GetTextureSize().x;
	float height = texture.GetTextureSize().y;

	if (width / 2 != MathUtil::Absolut(vertices.at(0).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(0).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(1).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(1).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(2).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(2).pos.y) ||
		width / 2 != MathUtil::Absolut(vertices.at(3).pos.x) ||
		height / 2 != MathUtil::Absolut(vertices.at(3).pos.y))
	{
		vertices.at(0).pos = { -(width / 2), +(height / 2), 0.0f };	// 左下
		vertices.at(1).pos = { -(width / 2), -(height / 2), 0.0f };	// 左上
		vertices.at(2).pos = { +(width / 2), +(height / 2), 0.0f }; // 右下
		vertices.at(3).pos = { +(width / 2), -(height / 2), 0.0f }; // 右上

		vertexBuffer->TransferToBuffer(vertices);
		vertexBuffer->Unmap();
	}
}

void Sprite::SetLayer(bool layer)
{
	this->layer = layer;
}
