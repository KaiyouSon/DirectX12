#include "main2.h"
#include "ViewProjection.h"
#include "Square.h"
#include "Cube.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"
#include "Random.h"
#include "TextureBuffer.h"
#include "DebugText.h"

Texture backTexture;
Texture objTexture;
Texture boxTexture;

Square* bg = new Square;
Cube* cube = new Cube;

// 画像の読み込み
void Load()
{
	backTexture = Texture::LoadTexture(L"Resources/bg.png");
	objTexture = Texture::LoadTexture(L"Resources/pic.png");

	bg->SetTexture(backTexture);
	cube->SetTexture(objTexture);

}

// 初期化処理
void Initialize()
{
	bg->Initialize(Square::view2D, Vec2(WIN_WIDTH, WIN_HEIGHT));
	cube->Initialize();

	View::GetInstance().SetPos(Vec3(0, 0, -30));
	View::GetInstance().SetTarget(Vec3::zero);
	View::GetInstance().SetUp(Vec3::up);
}

Transform transform2 =
{
	Vec3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
	Vec3(1,1,1),
	Vec3(0,0,0),
};

float angle = 270;
float length = 50;

Transform transform =
{
	Vec3(0,0,0),
	Vec3(1,1,1),
	Vec3(0,0,0),
};

// 更新処理
void Update()
{
	bg->Update(transform2);

	if (Input::Key().GetKey(DIK_LEFT))  angle--;
	if (Input::Key().GetKey(DIK_RIGHT)) angle++;

	if (Input::Key().GetKey(DIK_W)) transform.pos.y += 0.5;
	if (Input::Key().GetKey(DIK_S)) transform.pos.y -= 0.5;
	if (Input::Key().GetKey(DIK_D)) transform.pos.x += 0.5;
	if (Input::Key().GetKey(DIK_A)) transform.pos.x -= 0.5;


	cube->Update(transform);

	View::GetInstance().SetPos(Vec3(
		(float)(cos(Radian(angle)) * length), 0.0f, (float)(sin(Radian(angle)) * length)));

	DebugText::GetInstance()->
		Printf(0, 0, "transform = %f, %f, %f",
			transform.pos.x, transform.pos.y, transform.pos.z);

}

// 描画処理
void Draw3D()
{
	cube->Draw();
}

void Draw2D()
{
	bg->Draw();
}

// インスタンスのdelete
void Destroy()
{
	delete bg;
	delete cube;
}