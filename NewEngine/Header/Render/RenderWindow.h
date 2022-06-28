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
	unsigned int ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
	int GetWinWidth() { return WinWidth; };
	int GetWinHeight() { return WinHeight; };

	// ウィンドウハンドルの取得
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return wndClass.hInstance; }

	static RenderWindow& GetInstance();

private:
	RenderWindow() = default;
	~RenderWindow() = default;

	RenderWindow(const RenderWindow&) = delete;
	RenderWindow& operator=(const RenderWindow&) = delete;
	RenderWindow(const RenderWindow&&) = delete;
	RenderWindow& operator=(const RenderWindow&&) = delete;
};