#include "main2.h"
#include "ViewProjection.h"
#include "Util.h"
#include "MathUtil.h"
#include "InputManager.h"
#include "DebugManager.h"
#include "DrawManager.h"
#include "Sound.h"

Texture backTexture;
Texture objTexture;

Sound testSound;

Square* bg = new Square;
Cube* cube = new Cube;

// 画像の読み込み
void Load()
{
	backTexture = LoadTexture("Resources/bg.png");
	objTexture = LoadTexture("Resources/pic.png");
	testSound = LoadSoundWave("Resources/title_bgm.wav");
}

// 初期化処理
void Initialize()
{
	bg->Initialize(Square::view2D, Vec2(WIN_HALF_WIDTH, WIN_HALF_HEIGHT));
	cube->Initialize();

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

	if (pad->GetButton(BUTTON_START))  transform.pos.y += 0.5;

	view->SetPos(Vec3(
		(float)(cos(MathUtil::Radian(angle)) * length), 0.0f,
		(float)(sin(MathUtil::Radian(angle)) * length)));

	cube->Update(transform);

	//PlaySoundWave(testSound);

	Color color = Color::SetRGB(255, 255, 255);

	debugtext->Printf(0, 20, Color::white, "R = %f, G = %f, B = %f");
	debugtext->Printf(0, 40, Color::white, "H = %f, S = %f, V = %f");
}

// 描画処理
void Draw3D()
{
	cube->SetTexture(objTexture);
	cube->Draw();
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
	delete cube;
	delete bg;
}