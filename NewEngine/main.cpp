#include "NewEngine/NewEngine.h"
#include "NewEngine/main2.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/DataOperator.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowTitle("NewEngine");			// タイトル
	SetWindowSize(WIN_WIDTH, WIN_HEIGHT);	// サイズ
	SetBackgroundColor(25.5, 63.75, 127.5);	// 背景色
	NewEngineInit();	// エンジンの初期化
	Load();			// ゲーム内のロード処理
	Initialize();	// ゲーム内の初期化処理

	ObjectManager::GetInstance()->LoadData();
	// ゲームループ
	while (true)
	{
		////////////////////////////////////////////////////
		// ----------- ここから更新処理を記述 ----------- //
		////////////////////////////////////////////////////
		NewEngineUpda();	// エンジンの更新処理
		Update();			// ゲーム内の更新処理
		////////////////////////////////////////////////////
		// ---------- ここまでに更新処理を記述 ---------- //
		////////////////////////////////////////////////////
		NewEnginePreDraw();		// エンジン描画前処理
		////////////////////////////////////////////////////
		// ----------- ここから描画処理を記述 ----------- //
		////////////////////////////////////////////////////
		NewEngineSetDraw2D();	// エンジンの2D描画設定
		Draw2D();
		NewEngineSetDraw3D();	// エンジンの3D描画設定
		////////////////////////////////////////////////////
		// ---------- ここまでに描画処理を記述 ---------- //
		////////////////////////////////////////////////////
		NewEnginePostDraw();	// エンジン描画後処理

		// XボタンもしくはESCキーでゲームループを抜ける
		if (ProcessMessage() || key->GetKey(DIK_ESCAPE))
		{
			ObjectManager::GetInstance()->SaveData();
			break;
		}
	}

	Destroy();	// インスタンスの破棄
	NewEngineEnd();	// エンジンのエンド処理

	// 正常終了
	return 0;
}