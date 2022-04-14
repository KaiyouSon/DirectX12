#pragma once
#include <Windows.h>
class Win
{
private:
	// �E�B���h�E�T�C�Y
	const int WinWidth = 1280; // ����
	const int WinHeight = 720; // �c��

	WNDCLASSEX wndClass{};	// �E�B���h�E�N���X
	HWND hwnd = nullptr;	// �E�B���h�E�n���h��
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
};