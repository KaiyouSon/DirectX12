#include "Header/main2.h"
#include "Header/ViewProjection.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "Header/MathUtil.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "Header/DebugManager.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "Header/Sound.h"
#include "ImGUI/imgui.h"

Texture backTexture;
Texture objTexture;
Sound testSound;

Square* bg = new Square;
Object3D* model = new Object3D;
Object3D* model2 = new Object3D;
Cube* test = new Cube;

// 画像の読み込み
void Load()
{
	LoadBasicModel();
	backTexture = LoadTexture("Resources/bg.png");
	objTexture = LoadTexture("Resources/pic.png");
	testSound = LoadSoundWave("Resources/title_bgm.wav");
}

// 初期化処理
void Initialize()
{
	bg->Initialize(Square::view2D, Vec2(WIN_WIDTH, WIN_HEIGHT));
	test->Initialize();
	model->Initialize(monkey);


	model2->Initialize(cube);

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
	Vec3::one,
	Vec3::zero,
};

Transform transform3 =
{
	Vec3::zero,
	Vec3::one,
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
	model2->Update(transform3);
	test->Update(transform);

	//PlaySoundWave(testSound);

	Color color = Color::SetRGB(255, 255, 255);

	debugtext->Printf(0, 40, Color::white, "mousePos = %f, %f",
		mouse->GetMousePos().x, mouse->GetMousePos().y);
	ObjectManager::GetInstance()->Update();
}

// 描画処理
void Draw3D()
{
	//cube->SetTexture(objTexture);
	//cube->Draw();

	model->SetTexture(objTexture);
	model->Draw();
	model2->SetTexture(objTexture);
	//model2->Draw();

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
	delete test;
	delete bg;
	delete model;
	delete model2;

	ObjectManager::DestroyInstance();
}