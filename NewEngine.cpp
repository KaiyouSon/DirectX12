#include "NewEngine.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ShaderResourceView.h"
#include "ShaderCompiler.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"

#include "Util.h"

NewEngineBase* newEngine = new NewEngineBase;
ShaderResourceView* shaderResourceView = new ShaderResourceView;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
GraphicsCommand* graphicsCmd = new GraphicsCommand;

void NewEngineInit()
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif

	// WindowsAPI������
	NewEngineWindow::GetInstance().CreateGameWindow();

	// DirectX�̏���������
	newEngine->Initialize();

	// �V�F�[�_�[���\�[�X�r���[�̏�����
	shaderResourceView->Initialize();

	// �V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	graphicsPipeline->Initialize();
}

void NewEngineEnd()
{
	// �E�B���h�E�N���X��o�^����
	NewEngineWindow::GetInstance().TerminateGameWindow();

	delete newEngine;
	delete graphicsPipeline;
	delete graphicsCmd;
	delete shaderCompiler;
	delete shaderResourceView;
}

void ProcessMessage()
{
	//�E�C���h�E�Y�̃��b�Z�[�W����������
	NewEngineWindow::GetInstance().ProcessMessage();
}

void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT)
{
	NewEngineWindow::GetInstance().SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
}

void SetWindowTitle(const wchar_t* TITLE)
{
	NewEngineWindow::GetInstance().SetWindowTitle(TITLE);
}

bool CloseWindow()
{
	if (NewEngineWindow::GetInstance().GetProcessMessage() == WM_QUIT)
		return true;

	return false;
}

void SetBackgroundColor(int Red, int Green, int Blue)
{
	graphicsCmd->SetBackgroundColor(Red, Green, Blue);
}

void NewEnginePreDraw()
{
	graphicsCmd->PreUpdate();
}

void NewEnginePostDraw()
{
	graphicsCmd->PostUpdate();
}