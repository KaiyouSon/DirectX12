#include "NewEngine.h"
#include "main2.h"
#include "Input.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Util.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �E�B���h�E�^�C�g����ݒ肷��
	SetWindowTitle(L"NewEngine");

	// ��ʃT�C�Y��ݒ肷��
	SetWindowSize(WIN_WIDTH, WIN_HEIGHT);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(25.5, 63.75, 127.5);

	// NewEngine�̏�����
	NewEngineInit();

	// �摜�̓ǂݍ���
	Load();

	// ����������
	Initialize();

	// Input�̏���������
	Input::GetInstance().Initialize();

	// �r���[�v���W�F�N�V�����̏���������
	View::GetInstance().Initialize();

	// �f�o�b�O�e�L�X�g�̏�����
	DebugText::GetInstance()->Initialize(
		Texture::LoadTexture(L"Resources/debugfont.png"));

	// �Q�[�����[�v
	while (true)
	{
		//�E�C���h�E�Y�̃��b�Z�[�W����������
		ProcessMessage();

		// ----------- ��������X�V�������L�q ----------- //
		// ���͂̍X�V����
		Input::GetInstance().Update();

		// �X�V����
		Update();

		// ---------- �����܂łɍX�V�������L�q ---------- //
		// �`��O����
		NewEnginePreDraw();

		// ----------- ��������`�揈�����L�q ----------- //

		// 2D�`��̐ݒ�
		NewEngineSetDraw2D();

		// 2D�`�揈��
		Draw2D();
		DebugText::GetInstance()->DrawAll();
		
		// 3D�`��̐ݒ�
		NewEngineSetDraw3D();

		// 3D�`�揈��
		Draw3D();

		// ---------- �����܂łɕ`�揈�����L�q ---------- //

		// �`��㏈��
		NewEnginePostDraw();

		// X�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (CloseWindow())
		{
			break;
		}

		// ESC�L�[�ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (Input::Key().GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	// �C���X�^���X�̔j��
	Destroy();

	// �f�o�b�O�e�L�X�g�̔j��
	DebugText::GetInstance()->DestroyInstance();

	// NewEngine�̏I������
	NewEngineEnd();

	// ����I��
	return 0;
}