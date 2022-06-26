#include "Header/NewEngine.h"
#include "Header/main2.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "Header/Sound.h"
#include "Header/ViewProjection.h"
#include "NewEngine/Header/Developer/Debug/DebugManager.h"
#include "NewEngine/Gui/Header/GuiManager.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �E�B���h�E�^�C�g����ݒ肷��
	SetWindowTitle("NewEngine");

	// ��ʃT�C�Y��ݒ肷��
	SetWindowSize(WIN_WIDTH, WIN_HEIGHT);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(25.5, 63.75, 127.5);

	// NewEngine�̏�����
	NewEngineInit();

	// �����_���̏���������
	Random::Initialize();

	// Audio�̏���������
	SoundManager::GetInstance()->Initialize();

	// �r���[�v���W�F�N�V�����̏���������
	view->Initialize();

	// �f�o�b�O�}�l�[�W���̏�����
	DebugManager::GetInstance()->Initialize();

	GuiManager::GetInstance()->Initialize();

	// �摜�̓ǂݍ���
	Load();

	// ����������
	Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�E�C���h�E�Y�̃��b�Z�[�W����������
		ProcessMessage();

		// ----------- ��������X�V�������L�q ----------- //
		NewEngineUpda();

		// �f�o�b�O�}�l�[�W���̍X�V����
		DebugManager::GetInstance()->Update();

		GuiManager::GetInstance()->Update();
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

		// 3D�`��̐ݒ�
		NewEngineSetDraw3D();
		// 3D�`�揈��
		Draw3D();

		// 2D�`��̐ݒ�
		NewEngineSetDraw2D();
		// �f�o�b�O�}�l�[�W����2D�`��
		DebugManager::GetInstance()->Draw();

		GuiManager::GetInstance()->Draw();
		// ---------- �����܂łɕ`�揈�����L�q ---------- //

		// �`��㏈��
		NewEnginePostDraw();

		// X�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (CloseWindow())
		{
			break;
		}

		// ESC�L�[�ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (key->GetKey(DIK_ESCAPE))
		{
			break;
		}
	}

	view->DestroyInstance();

	// Audio�̔j��
	SoundManager::GetInstance()->DestroyInstance();

	// �f�o�b�O�}�l�[�W���̔j��
	DebugManager::GetInstance()->DestroyInstance();

	GuiManager::DestroyInstance();

	// �C���X�^���X�̔j��
	Destroy();

	// NewEngine�̏I������
	NewEngineEnd();

	// ����I��
	return 0;
}