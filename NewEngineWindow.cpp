#include "NewEngineWindow.h"
#include <Windows.h>

void NewEngineWindow::CreateGameWindow(int WIN_WIDTH, int WIN_HEIGHT)
{
	WinWidth = WIN_WIDTH;
	WinHeight = WIN_HEIGHT;

	// �E�B���h�E�N���X�̐ݒ�
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProc;		// �E�C���h�E�v���V�[�W����ݒ�
	wndClass.lpszClassName = L"DirectXGame";		// �E�B���h�E�N���X��
	wndClass.hInstance = GetModuleHandle(nullptr);	// �E�B���h�E�n���h��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// �J�[�\���w��

	// �E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&wndClass);
	// �E�B���h�E�T�C�Y{ X���W Y���W �c�� ���� }
	RECT wrc = { 0,0,WinWidth,WinHeight };
	// �����ŃT�C�Y�␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(
		wndClass.lpszClassName, // �N���X��
		L"DirectXGame",			// �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	// �W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �\��X���W(OS�ɔC����)
		CW_USEDEFAULT,			// �\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,	// �E�B���h�E����
		wrc.bottom - wrc.top,	// �E�B���h�E�c��
		nullptr,				// �e�E�B���h�E�n���h��
		nullptr,				// ���j���[�n���h��
		wndClass.hInstance,			// �Ăяo���A�v���P�[�V�����n���h��
		nullptr);				// �I�v�V����

	// �E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

void NewEngineWindow::TerminateGameWindow()
{
	// �E�B���h�E�N���X��o�^����
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

void NewEngineWindow::ProcessMessage()
{
	// ���b�Z�[�W������?
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);	// �L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg);	// �v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK NewEngineWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg)
	{
		// �E�B���h�E���j�󂳂ꂽ
	case WM_DESTROY:
		// OS�ɑ΂��āA�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	// �W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}