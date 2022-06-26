#include "Header/NewEngine.h"
#include "NewEngine/Header/Render/NewEngineBase.h"
#include "Header/NewEngineWindow.h"
#include "Header/ShaderResourceView.h"
#include "Header/ShaderCompiler.h"
#include "Header/GraphicsPipeline2D.h"
#include "Header/GraphicsPipeline3D.h"
#include "Header/GraphicsCommand.h"
#include "Header/DepthBuffer.h"
#include "Header/RootSignature.h"
#include "Header/Viewport.h"
#include "Header/ScissorRectangle.h"

#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include <wrl.h>
using namespace Microsoft::WRL;

Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

void NewEngineInit()
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf())))) {
		debugController.Get()->EnableDebugLayer();
	}
#endif

	// WindowsAPI������
	NewEngineWindow::GetInstance().CreateGameWindow();

	// DirectX�̏���������
	NewEngineBase::GetInstance()->Initialize();

	// �[�x�o�b�t�@�̏�����
	DepthBuffer::GetInstance()->Initialize();

	// �V�F�[�_�[���\�[�X�r���[�̏�����
	ShaderResourceView::GetInstance()->Initialize();

	// �V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	ShaderCompiler::GetInstance()->BasicVSCompile();
	ShaderCompiler::GetInstance()->BasicPSCompile();
	ShaderCompiler::GetInstance()->BasicPSCompile2();

	// ���[�g�V�O�l�`���̏�����
	RootSignature::GetInstance()->Initialize();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	GraphicsPipeline2D::GetInstance()->Initialize();
	GraphicsPipeline3D::GetInstance()->Initialize();

	// Input�̏�����
	Input::GetInstance()->Initialize();
}
void NewEngineUpda()
{
	// Input�̍X�V����
	Input::GetInstance()->Update();
}
void NewEngineEnd()
{
	// �E�B���h�E�N���X��o�^����
	NewEngineWindow::GetInstance().TerminateGameWindow();

	// �[�x�o�b�t�@�̔j��
	DepthBuffer::DestroyInstance();

	// �V�F�[�_�[���\�[�X�r���[�̔j��
	ShaderResourceView::DestroyInstance();

	// �V�F�[�_�[�R���p�C���[�̔j��
	ShaderCompiler::DestroyInstance();

	// ���[�g�V�O�l�`���̔j��
	RootSignature::DestroyInstance();

	// �O���t�B�b�N�X�p�C�v���C���̔j��
	GraphicsPipeline2D::DestroyInstance();
	GraphicsPipeline3D::DestroyInstance();

	//ComPtr<ID3D12Device> tmpDevice = NewEngineBase::GetInstance()->GetDevice().Get();
	// DirectX�̔j��
	NewEngineBase::DestroyInstance();

	//ID3D12DebugDevice* debugInterface;

	//if (SUCCEEDED(tmpDevice.Get()->QueryInterface(&debugInterface)))
	//{
	//	debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
	//	debugInterface->Release();
	//}

	Input::GetInstance()->DestoryInstance();

	delete viewport;
	delete scissorRectangle;
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
void SetWindowTitle(const std::string TITLE)
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
	GraphicsCommand::GetInstance().SetBackgroundColor(Red, Green, Blue);
}
void NewEnginePreDraw()
{
	GraphicsCommand::GetInstance().PreDraw();

	// �r���[�|�[�g�̏���
	viewport->Update();

	// �V�U�[��`�̏���
	scissorRectangle->Update();
}
void NewEngineSetDraw3D()
{
	GraphicsCommand::GetInstance().Draw3D();
}
void NewEngineSetDraw2D()
{
	GraphicsCommand::GetInstance().Draw2D();
}
void NewEnginePostDraw()
{
	GraphicsCommand::GetInstance().PostDraw();
}