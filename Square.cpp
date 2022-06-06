#include "Square.h"
#include "NewEngineBase.h"
#include "ViewProjection.h"
#include "ShaderResourceView.h"

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),

	ibArraySize(0), vbArraySize(0), viewType(view3D)
{
}

Square::~Square()
{
	//vertexBuffer->Unmap();

	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Square::Initialize(int viewType, Vec2 size)
{
	this->viewType = viewType;
	this->size = size;

	// 頂点データ
	if (viewType == view2D)
	{
		vertices[0] = { { -(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {0.0f, 1.0f} }; //左下
		vertices[1] = { { -(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {0.0f, 0.0f} }; //左上
		vertices[2] = { { +(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {1.0f, 1.0f} }; //右下
		vertices[3] = { { +(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {1.0f, 0.0f} }; //右上
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

	texture = TextureBuffer::GetDefaultTexture();
}

void Square::Update(const Transform& transform, Transform* parent)
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

void Square::Draw()
{
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

void Square::SetTexture(const Texture& texture)
{
	this->texture = texture;
}

void Square::SetColor(const Color& color)
{
	// 色の指定
	constantBuffer->SetColor(color);
}

void Square::SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize)
{
	float texLeft = cutPos.x / texture.GetTextureSize().x;
	float texRight = (cutPos.x + cutSize.x) / texture.GetTextureSize().x;
	float texUp = cutPos.y / texture.GetTextureSize().y;
	float texDown = (cutPos.y + cutSize.y) / texture.GetTextureSize().y;

	vertices[0].uv = { texLeft , texDown };	// 左下
	vertices[1].uv = { texLeft ,   texUp };	// 左上
	vertices[2].uv = { texRight ,texDown }; // 右下
	vertices[3].uv = { texRight ,  texUp }; // 右上

	vertexBuffer->TransferToBuffer();
}