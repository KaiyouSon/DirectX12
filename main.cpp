#include <DirectXMath.h>
using namespace DirectX;

#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Viewport.h"
#include "ScissorRectangle.h"

#include "ViewProjection.h"
#include "Square.h"
#include "Image.h"
#include "Cube.h"

NewEngineBase* newEngine = new NewEngineBase;
NewEngineWindow* newEngineWin = new NewEngineWindow;
GraphicsPipeline* graphicsPipeline = new GraphicsPipeline;
GraphicsCommand* graphicsCmd = new GraphicsCommand;
ShaderCompiler* shaderCompiler = new ShaderCompiler;
ShaderResourceView* shaderResourceView = new ShaderResourceView;
Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

ViewProjection* view = new ViewProjection;
Square* square = new Square;
Image* image = new Image;
Cube* cube = new Cube;

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif

	// WindowsAPI������
	newEngineWin->CreateGameWindow();

	// DirectX�̏���������
	newEngine->Initialize();

	// Input�̏���������
	input.Initialize();

	// �`�揉�������� ------------------------------------------------------------//
	square->Initialize();
	image->Initialize(L"Resources/pic.png");
	cube->Initialize();

	// �V�F�[�_�[���\�[�X�r���[�̏�����
	shaderResourceView->Initialize();

	// �V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	graphicsPipeline->Initialize();

	// ��ʂ̐F��ς���
	graphicsCmd->SetBackgroundColor(0x00, 0x00, 0x00);

	view->SetEye(XMFLOAT3(0, 0, -200));

	XMFLOAT3 pos1 = { 30,0,0 };
	XMFLOAT3 pos2 = { -30,0,0 };

	XMFLOAT3 scale1 = { 0.5,0.5,0.5 };
	XMFLOAT3 scale2 = { 0.5,0.5,0.5 };

	XMFLOAT3 rot1 = { 0,0,0 };

	// �Q�[�����[�v
	while (true)
	{
		newEngineWin->ProcessMessage();

		// DirectX���t���[�������@��������

		input.Update();

		if (input.GetKey(DIK_UP))		pos1.z++;
		if (input.GetKey(DIK_DOWN))		pos1.z--;
		if (input.GetKey(DIK_RIGHT))	pos1.x++;
		if (input.GetKey(DIK_LEFT))		pos1.x--;

		if (input.GetKey(DIK_W))		pos2.z++;
		if (input.GetKey(DIK_S))		pos2.z--;
		if (input.GetKey(DIK_D))		pos2.x++;
		if (input.GetKey(DIK_A))		pos2.x--;

		//square->Update(pos1, scale1, rot1, XMFLOAT4(255, 0, 0, 255));
		image->Update(pos2, scale2);
		cube->Update(pos1, scale1, XMFLOAT4(255, 255, 255, 255));

		graphicsCmd->PreUpdate();
		// �`��R�}���h��������

		// �r���[�|�[�g�̏���
		viewport->Update();

		// �V�U�[��`�̏���
		scissorRectangle->Update();

		{
			//---------- �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h ----------//
			// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
			newEngine->GetCommandList()->SetPipelineState(
				graphicsPipeline->GetPipelineState());
			newEngine->GetCommandList()->SetGraphicsRootSignature(
				graphicsPipeline->GetRootSignature());

			//------------- �v���~�e�B�u�`��̐ݒ�R�}���h�i�O�p�`���X�g�j -------------//
			// �v���~�e�B�u�`��̐ݒ�R�}���h
			newEngine->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
		}

		//square->Draw();
		image->Draw();
		cube->Draw();

		// �`��R�}���h�����܂�

		//��ʓ���ւ�
		graphicsCmd->PostUpdate();

		// DirectX���t���[�������@�����܂�

		// X�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (newEngineWin->GetProcessMessage() == WM_QUIT || input.GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	// �E�B���h�E�N���X��o�^����
	newEngineWin->TerminateGameWindow();

	delete newEngine;
	delete newEngineWin;
	delete graphicsPipeline;
	delete graphicsCmd;
	delete shaderCompiler;
	delete shaderResourceView;
	delete viewport;
	delete scissorRectangle;

	delete view;
	delete square;
	delete image;
	delete cube;

	return 0;
}