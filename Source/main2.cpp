#include "Header/main2.h"
#include "Header/ViewProjection.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Debug/DebugManager.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "Header/Sound.h"
#include "ImGUI/imgui.h"

Texture backTexture;
Texture objTexture;
Sound testSound;
Model barbla;

Square* bg = new Square;
Object3D* model = new Object3D;
Cube* testCube = new Cube;

// 画像の読み込み
void Load()
{
	LoadBasicModel();
	backTexture = LoadTexture("Resources/bg.png");
	objTexture = LoadTexture("Resources/pic.png");
	testSound = LoadSoundWave("Resources/title_bgm.wav");
	//barbla = LoadModel("Resources/barbla.obj");
}

// 初期化処理
void Initialize()
{
	bg->Initialize(Square::view2D, Vec2(WIN_WIDTH, WIN_HEIGHT));
	//model->Initialize(barbla);
	model->Initialize(monkey);
	testCube->Initialize();

	view->SetPos(Vec3(0, 0, -30));
	view->SetTarget(Vec3::zero);
	view->SetUp(Vec3::up);
}

Transform transform2 =
{
	Vec3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
	Vec3::one,
	Vec3::zero,
};

float angle = 270;
float length = 50;

Transform transform =
{
	Vec3::zero,
	Vec3::one * 10,
	Vec3::zero,
};

// 更新処理
void Update()
{
	bg->Update(transform2);

	if (key->GetKey(DIK_LEFT))  angle--;
	if (key->GetKey(DIK_RIGHT)) angle++;

	if (key->GetKey(DIK_W)) transform.pos.y += 0.5;
	if (key->GetKey(DIK_S)) transform.pos.y -= 0.5;
	if (key->GetKey(DIK_D)) transform.pos.x += 0.5;
	if (key->GetKey(DIK_A)) transform.pos.x -= 0.5;

	view->SetPos(Vec3(
		(float)(cos(MathUtil::Radian(angle)) * length), 0.0f,
		(float)(sin(MathUtil::Radian(angle)) * length)));

	model->Update(transform);

	testCube->Update(transform);


	//PlaySoundWave(testSound);

	Color color = Color::SetRGB(255, 255, 255);

	debugtext->Printf(0, 40, Color::white, "mousePos = %f, %f",
		mouse->GetMousePos().x, mouse->GetMousePos().y);
	ObjectManager::GetInstance()->Update();
}

// 描画処理
void Draw3D()
{
	model->Draw();

	ObjectManager::GetInstance()->Draw3D();
}

void Draw2D()
{
	bg->SetTexture(backTexture);
	//bg->Draw();
}

// インスタンスのdelete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	delete bg;
	delete model;
	delete testCube;

	ObjectManager::DestroyInstance();
}