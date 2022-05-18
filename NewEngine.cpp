#include "NewEngine.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "ShaderResourceView.h"
#include "ShaderCompiler.h"
#include "GraphicsPipeline2D.h"
#include "GraphicsPipeline3D.h"
#include "GraphicsCommand.h"
#include "DepthBuffer.h"
#include "RootSignature.h"
#include "Util.h"

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
	NewEngineBase::GetInstance().Initialize();

	// �[�x�o�b�t�@�̏�����
	DepthBuffer::GetInstance().Initialize();

	// �V�F�[�_�[���\�[�X�r���[�̏�����
	ShaderResourceView::GetInstance().Initialize();

	// �V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	ShaderCompiler::GetInstance().BasicVSCompile();
	ShaderCompiler::GetInstance().BasicPSCompile();

	// ���[�g�V�O�l�`���̏�����
	RootSignature::GetInstance().Initialize();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	GraphicsPipeline2D::GetInstance().Initialize();
	GraphicsPipeline3D::GetInstance().Initialize();
}

void NewEngineEnd()
{
	// �E�B���h�E�N���X��o�^����
	NewEngineWindow::GetInstance().TerminateGameWindow();

	delete graphicsCmd;
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

void SetBackgroundColor(float Red, float Green, float Blue)
{
	graphicsCmd->SetBackgroundColor(Red, Green, Blue);
}

void NewEnginePreDraw()
{
	graphicsCmd->PreDraw();
}

void NewEngineSetDraw3D()
{
	graphicsCmd->Draw3D();
}

void NewEngineSetDraw2D()
{
	graphicsCmd->Draw2D();
}

void NewEnginePostDraw()
{
	graphicsCmd->PostDraw();
}