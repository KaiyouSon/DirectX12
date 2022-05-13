#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Viewport.h"
#include "ScissorRectangle.h"
#include "MathUtil.h"
#include "Util.h"

#include "ViewProjection.h"
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
Image* image = new Image();
Image* bg = new Image(Vec2(WIN_WIDTH, WIN_HEIGHT));
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
	newEngineWin->CreateGameWindow(WIN_WIDTH, WIN_HEIGHT);

	// DirectXの初期化処理
	newEngine->Initialize();

	// Inputの初期化処理
	input.Initialize();

	// 描画初期化処理 ------------------------------------------------------------//
	// シェーダーリソースビューの初期化
	shaderResourceView->Initialize();

	// 画像の読み込み
	cube->LoadGraph(L"Resources/pic.png");
	image->LoadGraph(L"Resources/pic.png");
	bg->LoadGraph(L"Resources/bg.png");

	// 初期化処理
	cube->Initialize();
	image->Initialize(Image::view3D);
	bg->Initialize(Image::view2D);

	// シェーダファイルの読み込みとコンパイル
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// グラフィックスパイプラインの初期化
	graphicsPipeline->Initialize();

	// 画面の色を変える
	graphicsCmd->SetBackgroundColor(0x00, 0x00, 0x00);

	Transform transform =
	{
		XMFLOAT3(0,0,0),
		XMFLOAT3(1,1,1),
		XMFLOAT3(0,0,0),
	};
	float playerAngle = 0;

	Transform transform2 =
	{
		XMFLOAT3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
		XMFLOAT3(1,1,1),
		XMFLOAT3(0,0,0),
	};

	float viewAngle = 270;
	float viewAngle2 = 0;
	XMFLOAT3 viewPos = { 0,0,sinf(Radian(viewAngle)) * 300 };
	view->SetEye(XMFLOAT3(0, 0, -300));
	view->SetTarget(XMFLOAT3(0, 0, 0));

	// ゲームループ
	while (true)
	{
		newEngineWin->ProcessMessage();

		// DirectX毎フレーム処理　ここから

		input.Update();

		// Step1
		{
			// プレイヤー処理
			//if (input.GetKey(DIK_W)) transform.pos.y++;
			//if (input.GetKey(DIK_S)) transform.pos.y--;
			//if (input.GetKey(DIK_D)) transform.pos.x++;
			//if (input.GetKey(DIK_A)) transform.pos.x--;

			//playerAngle++;
			//if (playerAngle > 360) playerAngle = 0;
			//transform.rot.z = playerAngle;

			//image->Update(transform);

			//// カメラ処理
			//viewPos.z--;
			//view->SetEye(viewPos);
		}

		// Step2
		bg->Update(transform2);

		// Step3
		{
			if (input.GetKey(DIK_W)) transform.pos.y++;
			if (input.GetKey(DIK_S)) transform.pos.y--;
			if (input.GetKey(DIK_D)) transform.pos.x++;
			if (input.GetKey(DIK_A)) transform.pos.x--;

			if (input.GetKey(DIK_UP))	 transform.rot.x++;
			if (input.GetKey(DIK_DOWN))  transform.rot.x--;
			if (input.GetKey(DIK_LEFT))  transform.rot.y++;
			if (input.GetKey(DIK_RIGHT)) transform.rot.y--;

			cube->Update(transform);
		}

		graphicsCmd->PreUpdate();
		// 描画コマンドここから

		// ビューポートの処理
		viewport->Update();

		// シザー矩形の処理
		scissorRectangle->Update();

		//---------- パイプラインステートとルートシグネチャの設定コマンド ----------//
		// パイプラインステートとルートシグネチャの設定コマンド
		newEngine->GetCommandList()->SetPipelineState(
			graphicsPipeline->GetPipelineState());
		newEngine->GetCommandList()->SetGraphicsRootSignature(
			graphicsPipeline->GetRootSignature());


		// 描画コマンドここまで

		// 描画処理ここに書く

		bg->Draw();
		//image->Draw();
		cube->Draw();

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
	delete image;
	delete cube;

	return 0;
}