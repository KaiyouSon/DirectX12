#include <DirectXMath.h>
using namespace DirectX;

#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Viewport.h"
#include "ScissorRectangle.h"

#include "ViewProjection.h"
#include "Square.h"
#include "Image.h"
#include "Cube.h"

NewEngineBase* newEngine = new NewEngineBase;
NewEngineWindow* newEngineWin = new NewEngineWindow;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
GraphicsCommand* graphicsCmd = new GraphicsCommand;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
ShaderResourceView* shaderResourceView = new ShaderResourceView;
Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

ViewProjection* view = new ViewProjection;
Square* square = new Square;
Image* image = new Image;
Cube* cube = new Cube;

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

	// 描画初期化処理 ------------------------------------------------------------//
	square->Initialize();
	image->Initialize(L"Resources/pic.png");
	cube->Initialize();

	// シェーダーリソースビューの初期化
	shaderResourceView->Initialize();

	// シェーダファイルの読み込みとコンパイル
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// グラフィックスパイプラインの初期化
	graphicsPipeline->Initialize();

	// 画面の色を変える
	graphicsCmd->SetBackgroundColor(0x00, 0x00, 0x00);

	view->SetEye(XMFLOAT3(0, 0, -200));

	XMFLOAT3 pos1 = { 30,0,0 };
	XMFLOAT3 pos2 = { -30,0,0 };

	XMFLOAT3 scale1 = { 0.5,0.5,0.5 };
	XMFLOAT3 scale2 = { 0.5,0.5,0.5 };

	XMFLOAT3 rot1 = { 0,0,0 };

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

		//square->Update(pos1, scale1, rot1, XMFLOAT4(255, 0, 0, 255));
		image->Update(pos2, scale2);
		cube->Update(pos1, scale1, XMFLOAT4(255, 255, 255, 255));

		graphicsCmd->PreUpdate();
		// 描画コマンドここから

		// ビューポートの処理
		viewport->Update();

		// シザー矩形の処理
		scissorRectangle->Update();

		{
			//---------- パイプラインステートとルートシグネチャの設定コマンド ----------//
			// パイプラインステートとルートシグネチャの設定コマンド
			newEngine->GetCommandList()->SetPipelineState(
				graphicsPipeline->GetPipelineState());
			newEngine->GetCommandList()->SetGraphicsRootSignature(
				graphicsPipeline->GetRootSignature());

			//------------- プリミティブ形状の設定コマンド（三角形リスト） -------------//
			// プリミティブ形状の設定コマンド
			newEngine->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
		}

		//square->Draw();
		image->Draw();
		cube->Draw();

		// 描画コマンドここまで

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
	delete viewport;
	delete scissorRectangle;

	delete view;
	delete square;
	delete image;
	delete cube;

	return 0;
}