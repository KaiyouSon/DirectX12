#include "NewEngine.h"
#include "main2.h"
#include "Input.h"
#include "ViewProjection.h"
#include "Util.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ウィンドウタイトルを設定する
	SetWindowTitle(L"NewEngine");

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

	// ゲームループ
	while (true)
	{
		//ウインドウズのメッセージを処理する
		ProcessMessage();

		// ----------- ここから更新処理を記述 ----------- //
		// 入力の更新処理
		Input::GetInstance().Update();

		// 更新処理
		Update();

		// ---------- ここまでに更新処理を記述 ---------- //

		// 描画前処理
		NewEnginePreDraw();

		// ----------- ここから描画処理を記述 ----------- //

		// 描画処理
		Draw();

		// ---------- ここまでに描画処理を記述 ---------- //

		// 描画後処理
		NewEnginePostDraw();

		// Xボタンで終了メッセージが来たらゲームループを抜ける
		if (CloseWindow())
		{
			break;
		}

		// ESCキーで終了メッセージが来たらゲームループを抜ける
		if (Input::GetInstance().GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	// NewEngineの終了処理
	NewEngineEnd();

	// 正常終了
	return 0;
}