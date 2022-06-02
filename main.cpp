#include "NewEngine.h"
#include "main2.h"
#include "Input.h"
#include "ViewProjection.h"
#include "DebugManager.h"
#include "Util.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ウィンドウタイトルを設定する
	SetWindowTitle("NewEngine");

	// 画面サイズを設定する
	SetWindowSize(WIN_WIDTH, WIN_HEIGHT);

	// 画面の背景色を設定する
	SetBackgroundColor(25.5, 63.75, 127.5);

	// NewEngineの初期化
	NewEngineInit();

	// 画像の読み込み
	Load();

	// 初期化処理
	Initialize();

	// Inputの初期化処理
	Input::GetInstance().Initialize();

	// ビュープロジェクションの初期化処理
	View::GetInstance().Initialize();

	// デバッグマネージャの初期化
	DebugManager::GetInstance()->Initialize();

	// ゲームループ
	while (true)
	{
		//ウインドウズのメッセージを処理する
		ProcessMessage();

		// ----------- ここから更新処理を記述 ----------- //
		// 入力の更新処理
		Input::GetInstance().Update();
		// デバッグマネージャの更新処理
		DebugManager::GetInstance()->Update();

		// 更新処理
		Update();

		// ---------- ここまでに更新処理を記述 ---------- //
		// 描画前処理
		NewEnginePreDraw();

		// ----------- ここから描画処理を記述 ----------- //

		// 2D描画の設定
		NewEngineSetDraw2D();

		// 2D描画処理
		Draw2D();
		// デバッグマネージャの2D描画
		DebugManager::GetInstance()->Draw();

		// 3D描画の設定
		NewEngineSetDraw3D();

		// 3D描画処理
		Draw3D();

		// ---------- ここまでに描画処理を記述 ---------- //

		// 描画後処理
		NewEnginePostDraw();

		// Xボタンで終了メッセージが来たらゲームループを抜ける
		if (CloseWindow())
		{
			break;
		}

		// ESCキーで終了メッセージが来たらゲームループを抜ける
		if (Input::Key().GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	// デバッグマネージャの破棄
	DebugManager::GetInstance()->DestroyInstance();
	
	// インスタンスの破棄
	Destroy();

	// NewEngineの終了処理
	NewEngineEnd();

	// 正常終了
	return 0;
}