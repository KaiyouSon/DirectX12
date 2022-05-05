#include <DirectXMath.h>
using namespace DirectX;

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Square.h"

NewEngineBase* newEngine = new NewEngineBase;
NewEngineWindow* newEngineWin = new NewEngineWindow;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
GraphicsCommand* graphicsCmd = new GraphicsCommand;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
ShaderResourceView* shaderResourceView = new ShaderResourceView;

Square* square = new Square[2];

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

	// 描画初期化処理 ------------------------------------------------------------//

	for (int i = 0; i < 2; i++)
		square[i].Initialize();

	// シェーダファイルの読み込みとコンパイル
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	//textureBuffer->Initialize2();

	// シェーダーリソースビューの初期化
	shaderResourceView->Initialize();

	// グラフィックスパイプラインの初期化
	graphicsPipeline->Initialize();

	//FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // 青っぽい色

	XMFLOAT3 pos1 = { 0,0,0 };
	XMFLOAT3 pos2 = { 0,0,0 };

	// ゲームループ
	while (true)
	{
		newEngineWin->ProcessMessage();

		// DirectX毎フレーム処理　ここから

		input.Update();

		if (input.GetKey(DIK_UP))		pos1.z++;
		if (input.GetKey(DIK_DOWN))		pos1.z--;
		if (input.GetKey(DIK_RIGHT))	pos1.x++;
		if (input.GetKey(DIK_LEFT))		pos1.x--;

		if (input.GetKey(DIK_W))		pos2.z++;
		if (input.GetKey(DIK_S))		pos2.z--;
		if (input.GetKey(DIK_D))		pos2.x++;
		if (input.GetKey(DIK_A))		pos2.x--;

		graphicsCmd->PreUpdate();

#pragma region 描画コマンドここから


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
#pragma endregion 

		square[0].DrawBox(pos1, XMFLOAT4(255, 0, 0, 255));
		square[1].DrawBox(pos2, XMFLOAT4(0, 255, 0, 255));

#pragma region 描画コマンドここまで
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
	delete shaderCompiler;
	delete shaderResourceView;
	delete[] square;

	return 0;

}