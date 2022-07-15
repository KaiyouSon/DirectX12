#include "NewEngine/Header/Developer/Object/Object2D/Square.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"

const float Square::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),
	size(0, 0),
	ibArraySize(0), vbArraySize(0), viewType(view2D)
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
		vertices[0] = { { -0.5f, -0.5f, 0.0f },{},{0.0f, 1.0f} }; //左下
		vertices[1] = { { -0.5f, +0.5f, 0.0f },{},{0.0f, 0.0f} }; //左上
		vertices[2] = { { +0.5f, -0.5f, 0.0f },{},{1.0f, 1.0f} }; //右下
		vertices[3] = { { +0.5f, +0.5f, 0.0f },{},{1.0f, 0.0f} }; //右上
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

	texture = TextureBuffer::GetRenderTexture(
		{
			(float)RenderWindow::GetInstance().GetWinWidth(),
			(float)RenderWindow::GetInstance().GetWinHeight(),
		});

	HRESULT result;
	RenderBase* renderBase = RenderBase::GetInstance();

	//// テクスチャリソース設定
	//CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	RenderWindow::GetInstance().GetWinWidth(),
	//	(UINT)RenderWindow::GetInstance().GetWinHeight(),
	//	1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

	//// テクスチャバッファの生成
	//CD3DX12_HEAP_PROPERTIES texHeapProperties =
	//	CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	//CD3DX12_CLEAR_VALUE texClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor);

	//result = renderBase->GetDevice()->CreateCommittedResource(
	//	&texHeapProperties,
	//	D3D12_HEAP_FLAG_NONE,
	//	&texresDesc,
	//	D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
	//	//nullptr,
	//	&texClearValue,
	//	IID_PPV_ARGS(&texBuff));
	//assert(SUCCEEDED(result));

	//// テクスチャを赤クリア
	//{
	//	// 画素数
	//	const UINT pixelCont =
	//		RenderWindow::GetInstance().GetWinWidth() *
	//		RenderWindow::GetInstance().GetWinHeight();
	//	// 画像１行分のデータサイズ
	//	const UINT rowPitch = sizeof(UINT) * RenderWindow::GetInstance().GetWinWidth();
	//	// 画像全体のデータサイズ
	//	const UINT depthPitch = rowPitch * RenderWindow::GetInstance().GetWinHeight();
	//	// 画像イメージ
	//	UINT* img = new UINT[pixelCont];
	//	for (int i = 0; i < pixelCont; i++) { img[i] = 0xff0000ff; }

	//	// テクスチャバッファにデータ転送
	//	result = texBuff->WriteToSubresource(0, nullptr,
	//		img, rowPitch, depthPitch);
	//	assert(SUCCEEDED(result));
	//	delete[] img;
	//}

	//// SRV用デスクリプタヒープ設定
	//D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	//srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//srvDescHeapDesc.NumDescriptors = 1;
	//// SRV用デスクリプタヒープを作成
	//result = renderBase->GetDevice()->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	//assert(SUCCEEDED(result));

	//// SRV設定
	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// 設定構造体
	//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = 1;

	//// デスクリプタヒープにSRV作成
	//renderBase->GetDevice()->CreateShaderResourceView(texBuff.Get(),	// ビューと関連付けるバッファ
	//	&srvDesc,
	//	descHeapSRV->GetCPUDescriptorHandleForHeapStart());

	// RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc = {};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV用デスクリプタヒープを作成
	result = renderBase->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	// デスクリプタヒープにRTV作成
	renderBase->GetDevice()->CreateRenderTargetView(texture.buffer.Get(),
		//renderBase->GetDevice()->CreateRenderTargetView(texBuff.Get(),
		nullptr,
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

	// RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc = {};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	// RTV用デスクリプタヒープを作成
	result = renderBase->GetDevice()->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	// デスクリプタヒープの作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 深度地フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	renderBase->GetDevice()->CreateDepthStencilView(depthBuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart());

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
			view->matProjection2D;
	}
	if (viewType == view3D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			view->matView *
			view->matProjection3D;
	}
}

void Square::PreDrawScene()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	CD3DX12_RESOURCE_BARRIER resourceBarrier1 =
		//CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		CD3DX12_RESOURCE_BARRIER::Transition(texture.buffer.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET);

	//リソースバリアを変更（シェーダーリソース -> 描画可能）
	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier1);

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
	renderBase->GetCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	// 深度バッファのクリア
	renderBase->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void Square::PostDrawScene()
{
	// リソースバリアを変更（ 描画可能 -> シェーダーリソース）
	CD3DX12_RESOURCE_BARRIER resourceBarrier2 =
		//CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		CD3DX12_RESOURCE_BARRIER::Transition(texture.buffer.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	RenderBase::GetInstance()->GetCommandList()->
		ResourceBarrier(1, &resourceBarrier2);
}

void Square::Draw()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	renderBase->GetCommandList()->SetPipelineState(renderBase->pipelineState2D.Get());
	renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->rootSignature.Get());
	renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

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
		//SetDescriptorHeaps(1, descHeapSRV.GetAddressOf());
		SetDescriptorHeaps(1, RenderBase::GetInstance()->GetSrvDescHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	renderBase->GetCommandList()->
		//SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());
		SetGraphicsRootDescriptorTable(1, texture.GetGpuHandle());

	// 定数バッファビュー(CBV)の設定コマンド
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	renderBase->GetCommandList()->
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

Texture Square::GetRenderTexture()
{
	return texture;
}
