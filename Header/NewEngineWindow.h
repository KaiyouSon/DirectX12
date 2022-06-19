#pragma once
#include <Windows.h>
#include <string>
class NewEngineWindow
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

	/// <summary>
	/// ゲームウィンドウの作成 
	/// </summary>
	void CreateGameWindow();

	/// <summary>
	/// ゲームウィンドウの破棄
	/// </summary>
	void TerminateGameWindow();

	/// <summary>
	/// ウィンドウメッセージ処理
	/// </summary>
	void ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
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

	/// <summary>
	/// ウィンドウメッセージを取得する関数
	/// </summary>
	/// <returns> msg.message</returns>
	UINT GetProcessMessage() { return msg.message; }

	static NewEngineWindow& GetInstance();

private:
	NewEngineWindow() = default;
	~NewEngineWindow() = default;

	NewEngineWindow(const NewEngineWindow&) = delete;
	NewEngineWindow& operator=(const NewEngineWindow&) = delete;
	NewEngineWindow(const NewEngineWindow&&) = delete;
	NewEngineWindow& operator=(const NewEngineWindow&&) = delete;
};