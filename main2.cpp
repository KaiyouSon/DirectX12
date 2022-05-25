#include "main2.h"
#include "ViewProjection.h"
#include "Square.h"
#include "Cube.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "Random.h"
#include "TextureBuffer.h"

const int maxCube = 2;

Texture backTexture;
Texture objTexture;

Square* bg = new Square(Vec2(WIN_WIDTH, WIN_HEIGHT));
Cube* cube = new Cube[maxCube];

// 画像の読み込み
void Load()
{
	backTexture = Texture::LoadTexture(L"Resources/bg.png");
	objTexture = Texture::LoadTexture(L"Resources/pic.png");

	for (int i = 0; i < maxCube; i++)
		cube[i].SetTexture(objTexture);
	bg->SetTexture(backTexture);
}

Transform transform[maxCube] = {};

// 初期化処理
void Initialize()
{
	for (int i = 0; i < maxCube; i++)
		cube[i].Initialize();
	bg->Initialize(Square::view2D);

	View::GetInstance().SetPos(Vec3(0, 0, -30));
	View::GetInstance().SetTarget(Vec3(0, 0, 0));
	View::GetInstance().SetUp(Vec3(0, 1, 0));
}

Transform transform2 =
{
	Vec3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
	Vec3(1,1,1),
	Vec3(0,0,0),
};

float angle = 270;
float length = 50;

// 更新処理
void Update()
{
	bg->Update(transform2);

	if (Input::Key().GetKey(DIK_LEFT))  angle--;
	if (Input::Key().GetKey(DIK_RIGHT)) angle++;

	for (int i = 0; i < maxCube; i++)
	{
		transform[i].pos = Vec3::zero;
		transform[i].scale = Vec3::one;
		transform[i].rot = { 0,0,i * 45.0f };

		cube[i].Update(transform[i]);
	}

	View::GetInstance().SetPos(Vec3(
		(float)(cos(Radian(angle)) * length), 0.0f, (float)(sin(Radian(angle)) * length)));
}

// 描画処理
void Draw3D()
{
	for (int i = 0; i < maxCube; i++)
		cube[i].Draw();
}

void Draw2D()
{
	bg->Draw();
}

// インスタンスのdelete
void Delete()
{
	delete bg;
	delete[] cube;
}