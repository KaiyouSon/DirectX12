#include "NewEngine/Header/Developer/Object/Object2D/RenderTexture.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Developer/Component/Blend.h"

RenderTexture::RenderTexture() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer), size(0, 0)
{
	objectType = ObjectType::RenderTextureType;
}
RenderTexture::~RenderTexture()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void RenderTexture::Initialize(Vec2 size)
{
	HRESULT result;

	// 頂点データ
	vertices.push_back({ { -(size.x / 2), +(size.y / 2), 0.0f },{0.0f, 1.0f} });	//左下
	vertices.push_back({ { -(size.x / 2), -(size.y / 2), 0.0f },{0.0f, 0.0f} });	//左上
	vertices.push_back({ { +(size.x / 2), +(size.y / 2), 0.0f },{1.0f, 1.0f} });	//右下
	vertices.push_back({ { +(size.x / 2), -(size.y / 2), 0.0f },{1.0f, 0.0f} });	//右上

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

	Texture* tmpTex = TextureBuffer::GetRenderTexture(
		{
			(float)RenderWindow::GetInstance().GetWinWidth(),
			(float)RenderWindow::GetInstance().GetWinHeight(),
		});
	GetComponent<Texture>()->SetTexture(tmpTex);
	delete tmpTex;

	// RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc = {};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV用デスクリプタヒープを作成
	result = renderBase->GetDevice()->
		CreateDescriptorHeap(
			&rtvDescHeapDesc,
			IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	// レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	// シェーダーの計算結果をSRGBに変換して書き込む
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	// デスクリプタヒープにRTV作成
	ID3D12Resource* a = GetComponent<Texture>()->buffer.Get();
	auto b = a->GetDesc();

	renderBase->GetDevice()->CreateRenderTargetView(
		GetComponent<Texture>()->buffer.Get(),
		&rtvDesc,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	// 深度バッファリソースの設定
	CD3DX12_RESOURCE_DESC depthRecDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			RenderWindow::GetInstance().GetWinWidth(),
			(UINT)RenderWindow::GetInstance().GetWinHeight(),
			1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	// 深度バッファの生成
	CD3DX12_HEAP_PROPERTIES depthHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_CLEAR_VALUE depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	result = renderBase->GetDevice()->CreateCommittedResource(
		&depthHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthRecDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	// DSV用デスクリプタヒープを作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = renderBase->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	// デスクリプタヒープの作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvViewDesc = {};
	dsvViewDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 深度地フォーマット
	dsvViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	renderBase->GetDevice()->CreateDepthStencilView
	(
		depthBuff.Get(),
		&dsvViewDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart()
	);
}
void RenderTexture::Update()
{
	GetComponent<Transform>()->Update();

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->worldMat *
		view->matProjection2D;

	static Dirty<Color> colorDirty(color);
	if (colorDirty.GetisDirty(color) == true) constantBuffer->SetColor(color);

	color =
	{
		renderBase->clearColor[0] * 255,
		renderBase->clearColor[1] * 255,
		renderBase->clearColor[2] * 255,
		renderBase->clearColor[3] * 255,
	};
}

void RenderTexture::PreDrawScene()
{
	CD3DX12_RESOURCE_BARRIER resourceBarrier;
	resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetComponent<Texture>()->buffer.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	//リソースバリアを変更（シェーダーリソース -> 描画可能）
	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier);

	// レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH = descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	// 深度ステンシルビュー用ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	// レンダーターゲットをセット
	renderBase->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	// ビューポートの設定
	CD3DX12_VIEWPORT viewport = CD3DX12_VIEWPORT(
		0.0f, 0.0f,
		RenderWindow::GetInstance().GetWinWidth(),
		RenderWindow::GetInstance().GetWinHeight());

	renderBase->GetCommandList()->RSSetViewports(1, &viewport);
	// シザリング矩形の設定
	CD3DX12_RECT scissorRect = CD3DX12_RECT(
		0, 0,
		RenderWindow::GetInstance().GetWinWidth(),
		RenderWindow::GetInstance().GetWinHeight());

	renderBase->GetCommandList()->RSSetScissorRects(1, &scissorRect);

	// 全画面クリア
	renderBase->GetCommandList()->ClearRenderTargetView(rtvH, renderBase->clearColor, 0, nullptr);
	// 深度バッファのクリア
	renderBase->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
void RenderTexture::PostDrawScene()
{
	// リソースバリアを変更（描画可能 -> シェーダーリソース）
	CD3DX12_RESOURCE_BARRIER resourceBarrier;
	resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetComponent<Texture>()->buffer.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier);
}
void RenderTexture::Draw()
{
	GetComponent<Blend>()->SetBlendMode(BlendMode::AlphaRenderTexture);
	//GetComponent<Blend>()->SetBlendMode(BlendMode::Alpha2D);

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

void RenderTexture::SetColor(const Color& color)
{
	// 色の指定
	constantBuffer->SetColor(color);
}
void RenderTexture::SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize)
{
	//float texLeft = cutPos.x / texture.GetTextureSize().x;
	//float texRight = (cutPos.x + cutSize.x) / texture.GetTextureSize().x;
	//float texUp = cutPos.y / texture.GetTextureSize().y;
	//float texDown = (cutPos.y + cutSize.y) / texture.GetTextureSize().y;

	//vertices[0].uv = { texLeft , texDown };	// 左下
	//vertices[1].uv = { texLeft ,   texUp };	// 左上
	//vertices[2].uv = { texRight ,texDown }; // 右下
	//vertices[3].uv = { texRight ,  texUp }; // 右上

	//vertexBuffer->TransferToBuffer();
}

Texture* RenderTexture::GetRenderTexture()
{
	return GetComponent<Texture>();
}

std::unique_ptr<RenderTexture> sceneViewTexture(new RenderTexture);