#include "NewEngine/NewEngine.h"
#include "NewEngine/main2.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/DataOperator.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowTitle("NewEngine");			// �^�C�g��
	SetWindowSize(WIN_WIDTH, WIN_HEIGHT);	// �T�C�Y
	SetBackgroundColor(25.5, 63.75, 127.5);	// �w�i�F
	NewEngineInit();	// �G���W���̏�����
	DataOperator::GetInstance()->LoadData();
	Load();			// �Q�[�����̃��[�h����
	Initialize();	// �Q�[�����̏���������

	//ObjectManager::GetInstance()->LoadData();
	// �Q�[�����[�v
	while (true)
	{
		////////////////////////////////////////////////////
		// ----------- ��������X�V�������L�q ----------- //
		////////////////////////////////////////////////////
		NewEngineUpda();	// �G���W���̍X�V����
		Update();			// �Q�[�����̍X�V����
		////////////////////////////////////////////////////
		// ---------- �����܂łɍX�V�������L�q ---------- //
		////////////////////////////////////////////////////
		NewEnginePreDraw();		// �G���W���`��O����
		////////////////////////////////////////////////////
		// ----------- ��������`�揈�����L�q ----------- //
		////////////////////////////////////////////////////
		NewEneineDraw();		// �G���W���̕`�揈��
		DrawLine();
		////////////////////////////////////////////////////
		// ---------- �����܂łɕ`�揈�����L�q ---------- //
		////////////////////////////////////////////////////
		NewEnginePostDraw();	// �G���W���`��㏈��
	
		// X�{�^����������ESC�L�[�ŃQ�[�����[�v�𔲂���
		if (ProcessMessage() || key->GetKey(DIK_ESCAPE))
		{
			DataOperator::GetInstance()->SaveData();
			break;
		}
	}

	Destroy();	// �C���X�^���X�̔j��
	NewEngineEnd();	// �G���W���̃G���h����

	// ����I��
	return 0;
}