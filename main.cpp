#include <DirectXMath.h>
using namespace DirectX;

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "TextureBuffer.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Sprite.h"

#include "Transform.h"
#include "ViewProjection.h"

NewEngineBase* newEngine = new NewEngineBase;
NewEngineWindow* newEngineWin = new NewEngineWindow;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
GraphicsCommand* graphicsCmd = new GraphicsCommand;
VertexBuffer* vertexBuffer = new VertexBuffer;
IndexBuffer* indexBuffer = new IndexBuffer;
ConstantBuffer* constantBuffer = new ConstantBuffer;
TextureBuffer* textureBuffer = new TextureBuffer;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
ShaderResourceView* shaderResourceView = new ShaderResourceView;
Sprite* sprite = new Sprite;

Transform* transform = new Transform;
ViewProjection* viewProjection = new ViewProjection;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif

	// WindowsAPI初期化
	newEngineWin->CreateGameWindow();

	// DirectXの初期化処理
	newEngine->Initialize();

	// Inputの初期化処理
	input.Initialize();

	HRESULT result;

#pragma region 描画初期化処理

	//------------------- グラフィックボートのアダプタを列挙 -------------------//
	sprite->Initialize();

	// シェーダファイルの読み込みとコンパイル
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();


	//--------------------- グラフィックスパイプライン設定 ---------------------//
	//graphicsPipeline->Initialize();

	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	textureBuffer->Initialize1();
	//textureBuffer->Initialize2();


	//// 単位行列を代入
	//constMapTransform->mat = XMMatrixIdentity();

	//constMapTransform->mat.r[0].m128_f32[0] = 2.0f / newEngineWin->GetWinWidth();
	//constMapTransform->mat.r[1].m128_f32[1] = -2.0f / newEngineWin->GetWinHeight();

	//constMapTransform->mat.r[3].m128_f32[0] = -1.0f;
	//constMapTransform->mat.r[3].m128_f32[1] = 1.0f;

	// 並行投影行列の計算
	constantBuffer->constMapTransform->mat = XMMatrixOrthographicOffCenterLH(
		0, newEngineWin->GetWinWidth(),
		newEngineWin->GetWinHeight(), 0,
		0, 1);

	viewProjection->Initialize();

	shaderResourceView->Initialize();

	// ハンドルの指す位置にシェーダーリソースビュー作成
	newEngine->GetDevice()->CreateShaderResourceView(
		textureBuffer->GetTextureBuff(),
		shaderResourceView->GetsrvDescAddress(),
		shaderResourceView->GetsrvHandle());

	//--------------------- グラフィックスパイプライン設定 ---------------------//
	graphicsPipeline->Initialize();

#pragma endregion

	//FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // 青っぽい色

	// ゲームループ
	while (true)
	{
		newEngineWin->ProcessMessage();

		// DirectX毎フレーム処理　ここから

		input.Update();

		if (input.GetKey(DIK_UP))		transform->pos.z++;
		if (input.GetKey(DIK_DOWN))		transform->pos.z--;
		if (input.GetKey(DIK_RIGHT))	transform->pos.x++;
		if (input.GetKey(DIK_LEFT))		transform->pos.x--;

		transform->Update();

		// 定数バッファに転送
		constantBuffer->constMapTransform->mat = 
			transform->matWorld * viewProjection->matView * viewProjection->matProjection;

		graphicsCmd->PreUpdate();

#pragma region グラフィックスコマンド

		// ４．描画コマンドここから

		//----------------------- ビューポートの設定コマンド -----------------------//
		// ビューポート設定コマンド
		D3D12_VIEWPORT viewport{};
		viewport.Width = newEngineWin->GetWinWidth();
		viewport.Height = newEngineWin->GetWinHeight();
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		// ビューポート設定コマンドを、コマンドリストに積む
		newEngine->GetCommandList()->RSSetViewports(1, &viewport);

		//------------------------ シザー矩形の設定コマンド ------------------------//
		// シザー矩形
		D3D12_RECT scissorRect{};
		scissorRect.left = 0; // 切り抜き座標左
		scissorRect.right = scissorRect.left + newEngineWin->GetWinWidth(); // 切り抜き座標右
		scissorRect.top = 0; // 切り抜き座標上
		scissorRect.bottom = scissorRect.top + newEngineWin->GetWinHeight(); // 切り抜き座標下
		// シザー矩形設定コマンドを、コマンドリストに積む
		newEngine->GetCommandList()->RSSetScissorRects(1, &scissorRect);

		//---------- パイプラインステートとルートシグネチャの設定コマンド ----------//
		// パイプラインステートとルートシグネチャの設定コマンド
		newEngine->GetCommandList()->SetPipelineState(
			graphicsPipeline->GetPipelineState());
		newEngine->GetCommandList()->SetGraphicsRootSignature(
			graphicsPipeline->GetRootSignature());

		//------------- プリミティブ形状の設定コマンド（三角形リスト） -------------//
		// プリミティブ形状の設定コマンド
		newEngine->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

		// SRVヒープの設定コマンド
		newEngine->GetCommandList()->SetDescriptorHeaps(
			1, shaderResourceView->GetsrvHeapAddress());
		// SRVヒープの先頭ハンドルを取得
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle =
			shaderResourceView->GetsrvHeap()->GetGPUDescriptorHandleForHeapStart();
		// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
		newEngine->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);


		sprite->DrawBox(XMFLOAT4(255,255,255,255));

		// ４．描画コマンドここまで

#pragma endregion 

		//画面入れ替え
		graphicsCmd->PostUpdate();

		// DirectX毎フレーム処理　ここまで

		// Xボタンで終了メッセージが来たらゲームループを抜ける
		if (newEngineWin->GetProcessMessage() == WM_QUIT || input.GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	// ウィンドウクラスを登録解除
	newEngineWin->TerminateGameWindow();

	delete newEngine;
	delete newEngineWin;
	delete graphicsPipeline;
	delete graphicsCmd;
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
	delete textureBuffer;
	delete shaderCompiler;
	delete shaderResourceView;
	delete sprite;

	delete transform;
	delete viewProjection;

	return 0;

}