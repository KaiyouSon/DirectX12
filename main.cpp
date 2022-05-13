#include "Input.h"
#include "NewEngineBase.h"
#include "NewEngineWindow.h"
#include "GraphicsPipeline.h"
#include "GraphicsCommand.h"
#include "ShaderCompiler.h"
#include "ShaderResourceView.h"
#include "Viewport.h"
#include "ScissorRectangle.h"
#include "MathUtil.h"
#include "Util.h"

#include "ViewProjection.h"
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
Image* image = new Image();
Image* bg = new Image(Vec2(WIN_WIDTH, WIN_HEIGHT));
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
	newEngineWin->CreateGameWindow(WIN_WIDTH, WIN_HEIGHT);

	// DirectX�̏���������
	newEngine->Initialize();

	// Input�̏���������
	input.Initialize();

	// �`�揉�������� ------------------------------------------------------------//
	// �V�F�[�_�[���\�[�X�r���[�̏�����
	shaderResourceView->Initialize();

	// �摜�̓ǂݍ���
	cube->LoadGraph(L"Resources/pic.png");
	image->LoadGraph(L"Resources/pic.png");
	bg->LoadGraph(L"Resources/bg.png");

	// ����������
	cube->Initialize();
	image->Initialize(Image::view3D);
	bg->Initialize(Image::view2D);

	// �V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	shaderCompiler->BasicVSCompile();
	shaderCompiler->BasicPSCompile();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	graphicsPipeline->Initialize();

	// ��ʂ̐F��ς���
	graphicsCmd->SetBackgroundColor(0x00, 0x00, 0x00);

	Transform transform =
	{
		XMFLOAT3(0,0,0),
		XMFLOAT3(1,1,1),
		XMFLOAT3(0,0,0),
	};
	float playerAngle = 0;

	Transform transform2 =
	{
		XMFLOAT3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
		XMFLOAT3(1,1,1),
		XMFLOAT3(0,0,0),
	};

	float viewAngle = 270;
	float viewAngle2 = 0;
	XMFLOAT3 viewPos = { 0,0,sinf(Radian(viewAngle)) * 300 };
	view->SetEye(XMFLOAT3(0, 0, -300));
	view->SetTarget(XMFLOAT3(0, 0, 0));

	// �Q�[�����[�v
	while (true)
	{
		newEngineWin->ProcessMessage();

		// DirectX���t���[�������@��������

		input.Update();

		// Step1
		{
			// �v���C���[����
			//if (input.GetKey(DIK_W)) transform.pos.y++;
			//if (input.GetKey(DIK_S)) transform.pos.y--;
			//if (input.GetKey(DIK_D)) transform.pos.x++;
			//if (input.GetKey(DIK_A)) transform.pos.x--;

			//playerAngle++;
			//if (playerAngle > 360) playerAngle = 0;
			//transform.rot.z = playerAngle;

			//image->Update(transform);

			//// �J��������
			//viewPos.z--;
			//view->SetEye(viewPos);
		}

		// Step2
		bg->Update(transform2);

		// Step3
		{
			if (input.GetKey(DIK_W)) transform.pos.y++;
			if (input.GetKey(DIK_S)) transform.pos.y--;
			if (input.GetKey(DIK_D)) transform.pos.x++;
			if (input.GetKey(DIK_A)) transform.pos.x--;

			if (input.GetKey(DIK_UP))	 transform.rot.x++;
			if (input.GetKey(DIK_DOWN))  transform.rot.x--;
			if (input.GetKey(DIK_LEFT))  transform.rot.y++;
			if (input.GetKey(DIK_RIGHT)) transform.rot.y--;

			cube->Update(transform);
		}

		graphicsCmd->PreUpdate();
		// �`��R�}���h��������

		// �r���[�|�[�g�̏���
		viewport->Update();

		// �V�U�[��`�̏���
		scissorRectangle->Update();

		//---------- �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h ----------//
		// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		newEngine->GetCommandList()->SetPipelineState(
			graphicsPipeline->GetPipelineState());
		newEngine->GetCommandList()->SetGraphicsRootSignature(
			graphicsPipeline->GetRootSignature());


		// �`��R�}���h�����܂�

		// �`�揈�������ɏ���

		bg->Draw();
		//image->Draw();
		cube->Draw();

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
	delete image;
	delete cube;

	return 0;
}