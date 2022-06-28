#pragma once
#include <Windows.h>
#include <string>
class RenderWindow
{
private:
	// �E�B���h�E�T�C�Y
	int WinWidth = 1280; // ����
	int WinHeight = 720; // �c��
	std::string TITLE = "error";

	WNDCLASSEX wndClass{};	// �E�B���h�E�N���X
	HWND hwnd;	// �E�B���h�E�n���h��
	MSG msg{};	//���b�Z�[�W
public:
	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	/// <returns>����</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:

	// �Q�[���E�B���h�E�̍쐬 
	void CreateGameWindow();

	// �Q�[���E�B���h�E�̔j��
	void TerminateGameWindow();

	// �E�B���h�E���b�Z�[�W����
	unsigned int ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
	int GetWinWidth() { return WinWidth; };
	int GetWinHeight() { return WinHeight; };

	// �E�B���h�E�n���h���̎擾
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