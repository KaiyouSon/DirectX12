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
	void ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
	// �E�B���h�E�̉������擾����֐�
	int GetWinWidth() { return WinWidth; };

	// �E�B���h�E�̏c�����擾����֐�
	int GetWinHeight() { return WinHeight; };

	// �E�B���h�E�̉����̔������擾����֐�
	int GetHalfWinWidth() { return WinWidth / 2; };

	// �E�B���h�E�̏c���̔������擾����֐�
	int GetHalfWinHeight() { return WinHeight / 2; };

	// �E�B���h�E�n���h���̎擾
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return wndClass.hInstance; }

	// �E�B���h�E���b�Z�[�W���擾����֐�
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