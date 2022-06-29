#include "NewEngine/main2.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Debug/DebugManager.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Debug/DebugCamera.h"
#include "NewEngine/Header/Developer/Sound.h"
#include "ImGUI/imgui.h"

Texture* backTexture;
Texture* objTexture;
Sound testSound;
Model barbla;

Square* bg = new Square;
Cube* testCube = new Cube;

// �摜�̓ǂݍ���
void Load()
{
	LoadBasicModel();
	gameTextureList->PushToTextureList(LoadTexture("Resources/bg.png"), "bg");
	gameTextureList->PushToTextureList(LoadTexture("Resources/pic.png"), "obj");

	backTexture = LoadTexture("Resources/bg.png");
	objTexture = LoadTexture("Resources/pic.png");
	testSound = LoadSoundWave("Resources/title_bgm.wav");

	//barbla = LoadModel("Resources/barbla.obj");
}

// ����������
void Initialize()
{
	bg->Initialize(Square::view2D, Vec2(WIN_WIDTH, WIN_HEIGHT));
	//model->Initialize(barbla);
	//model->Initialize(monkey);
	testCube->Initialize();

	//ObjectManager::GetInstance()->CreateCube();

	view->SetPos(Vec3(0, 0, -50));
	view->SetTarget(Vec3::zero);
	view->SetUp(Vec3::up);

	DebugCamera::GetInstance()->Initialize();
}

Transform transform2 =
{
	Vec3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
	Vec3::one,
	Vec3::zero,
};

float angle = 270;
float length = 50;

// �X�V����
void Update()
{
	bg->Update(transform2);

	//if (key->GetKey(DIK_LEFT))  angle--;
	//if (key->GetKey(DIK_RIGHT)) angle++;

	//view->SetPos(Vec3(
	//	(float)(cos(MathUtil::Radian(angle)) * length), 0.0f,
	//	(float)(sin(MathUtil::Radian(angle)) * length)));

	//PlaySoundWave(testSound);

	DebugCamera::GetInstance()->Update();
}

// �`�揈��
void Draw3D()
{

}

void Draw2D()
{
	//bg->SetTexture(backTexture);
	//bg->Draw();
}

// �C���X�^���X��delete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	//delete model;
	delete bg;
	delete testCube;
	delete gameTextureList;

	UnLoadTexture(backTexture);
	UnLoadTexture(objTexture);
}