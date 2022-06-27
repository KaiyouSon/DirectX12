#pragma once
#include <Windows.h>
#include <string>
class RenderWindow
{
private:
	// ウィンドウサイズ
	int WinWidth = 1280; // 横幅
	int WinHeight = 720; // 縦幅
	std::string TITLE = "error";

	WNDCLASSEX wndClass{};	// ウィンドウクラス
	HWND hwnd;	// ウィンドウハンドル
	MSG msg{};	//メッセージ
public:
	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	/// <returns>成否</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:

	// ゲームウィンドウの作成 
	void CreateGameWindow();

	// ゲームウィンドウの破棄
	void TerminateGameWindow();

	// ウィンドウメッセージ処理
	void ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
	// ウィンドウの横幅を取得する関数
	int GetWinWidth() { return WinWidth; };

	// ウィンドウの縦幅を取得する関数
	int GetWinHeight() { return WinHeight; };

	// ウィンドウの横幅の半分を取得する関数
	int GetHalfWinWidth() { return WinWidth / 2; };

	// ウィンドウの縦幅の半分を取得する関数
	int GetHalfWinHeight() { return WinHeight / 2; };

	// ウィンドウハンドルの取得
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return wndClass.hInstance; }

	// ウィンドウメッセージを取得する関数
	UINT GetProcessMessage() { return msg.message; }

	static RenderWindow& GetInstance();

private:
	RenderWindow() = default;
	~RenderWindow() = default;

	RenderWindow(const RenderWindow&) = delete;
	RenderWindow& operator=(const RenderWindow&) = delete;
	RenderWindow(const RenderWindow&&) = delete;
	RenderWindow& operator=(const RenderWindow&&) = delete;
};