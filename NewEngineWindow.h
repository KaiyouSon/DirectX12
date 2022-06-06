#pragma once
#include <Windows.h>
#include <string>
class NewEngineWindow
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

	/// <summary>
	/// �Q�[���E�B���h�E�̍쐬 
	/// </summary>
	void CreateGameWindow();

	/// <summary>
	/// �Q�[���E�B���h�E�̔j��
	/// </summary>
	void TerminateGameWindow();

	/// <summary>
	/// �E�B���h�E���b�Z�[�W����
	/// </summary>
	void ProcessMessage();

	void SetWindowTitle(const std::string TITLE);
	void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);

public:
	/// <summary>
	/// �E�B���h�E�̉������擾����֐�
	/// </summary>
	/// <returns>�E�B���h�E�̉���</returns>
	int GetWinWidth() { return WinWidth; };

	/// <summary>
	/// �E�B���h�E�̏c�����擾����֐�
	/// </summary>
	/// <returns>�E�B���h�E�̏c��</returns>
	int GetWinHeight() { return WinHeight; };

	/// <summary>
	/// �E�B���h�E�̉����̔������擾����֐�
	/// </summary>
	/// <returns>�E�B���h�E�̉����̔���</returns>
	int GetHalfWinWidth() { return WinWidth / 2; };

	/// <summary>
	/// �E�B���h�E�̏c���̔������擾����֐�
	/// </summary>
	/// <returns>�E�B���h�E�̏c���̔���</returns>
	int GetHalfWinHeight() { return WinHeight / 2; };

	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return wndClass.hInstance; }

	/// <summary>
	/// �E�B���h�E���b�Z�[�W���擾����֐�
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