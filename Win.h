#pragma once
#include <Windows.h>
class Win
{
private:
	// ウィンドウサイズ
	const int WinWidth = 1280; // 横幅
	const int WinHeight = 720; // 縦幅

	WNDCLASSEX wndClass{};	// ウィンドウクラス
	HWND hwnd = nullptr;	// ウィンドウハンドル
public:
	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	/// <returns>成否</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:

	/// <summary>
	/// ゲームウィンドウの作成 
	/// </summary>
	void CreateGameWindow();

	/// <summary>
	/// ゲームウィンドウの破棄
	/// </summary>
	void TerminateGameWindow();

	/// <summary>
	/// ウィンドウの横幅を取得する関数
	/// </summary>
	/// <returns>ウィンドウの横幅</returns>
	int GetWinWidth() { return WinWidth; };

	/// <summary>
	/// ウィンドウの縦幅を取得する関数
	/// </summary>
	/// <returns>ウィンドウの縦幅</returns>
	int GetWinHeight() { return WinHeight; };

	/// <summary>
	/// ウィンドウの横幅の半分を取得する関数
	/// </summary>
	/// <returns>ウィンドウの横幅の半分</returns>
	int GetHalfWinWidth() { return WinWidth / 2; };

	/// <summary>
	/// ウィンドウの縦幅の半分を取得する関数
	/// </summary>
	/// <returns>ウィンドウの縦幅の半分</returns>
	int GetHalfWinHeight() { return WinHeight / 2; };

	/// <summary>
	/// ウィンドウハンドルの取得
	/// </summary>
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return wndClass.hInstance; }
};