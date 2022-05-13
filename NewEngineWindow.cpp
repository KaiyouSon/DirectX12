#include "NewEngineWindow.h"
#include <Windows.h>

void NewEngineWindow::CreateGameWindow(int WIN_WIDTH, int WIN_HEIGHT)
{
	WinWidth = WIN_WIDTH;
	WinHeight = WIN_HEIGHT;

	// ウィンドウクラスの設定
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProc;		// ウインドウプロシージャを設定
	wndClass.lpszClassName = L"DirectXGame";		// ウィンドウクラス名
	wndClass.hInstance = GetModuleHandle(nullptr);	// ウィンドウハンドル
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// カーソル指定

	// ウィンドウクラスをOSに登録
	RegisterClassEx(&wndClass);
	// ウィンドウサイズ{ X座標 Y座標 縦幅 横幅 }
	RECT wrc = { 0,0,WinWidth,WinHeight };
	// 自動でサイズ補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウオブジェクトの生成
	hwnd = CreateWindow(
		wndClass.lpszClassName, // クラス名
		L"DirectXGame",			// タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	// 標準的なウィンドウスタイル
		CW_USEDEFAULT,			// 表示X座標(OSに任せる)
		CW_USEDEFAULT,			// 表示Y座標(OSに任せる)
		wrc.right - wrc.left,	// ウィンドウ横幅
		wrc.bottom - wrc.top,	// ウィンドウ縦幅
		nullptr,				// 親ウィンドウハンドル
		nullptr,				// メニューハンドル
		wndClass.hInstance,			// 呼び出しアプリケーションハンドル
		nullptr);				// オプション

	// ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

void NewEngineWindow::TerminateGameWindow()
{
	// ウィンドウクラスを登録解除
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

void NewEngineWindow::ProcessMessage()
{
	// メッセージがある?
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);	// キー入力メッセージの処理
		DispatchMessage(&msg);	// プロシージャにメッセージを送る
	}
}

// ウィンドウプロシージャ
LRESULT CALLBACK NewEngineWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
		// ウィンドウが破壊された
	case WM_DESTROY:
		// OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}