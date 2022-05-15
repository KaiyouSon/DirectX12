#include "main2.h"
#include "ViewProjection.h"
#include "Image.h"
#include "Cube.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"

Image* bg = new Image(Vec2(WIN_WIDTH, WIN_HEIGHT));
Cube* cube = new Cube;

// 画像の読み込み
void Load()
{
	cube->LoadGraph(L"Resources/pic.png");
	bg->LoadGraph(L"Resources/bg.png");
}

// 初期化処理
void Initialize()
{
	cube->Initialize();
	bg->Initialize(Image::view2D);

	View::GetInstance().SetEye(XMFLOAT3(0, 0, -30));
	View::GetInstance().SetTarget(XMFLOAT3(0, 0, 0));
}

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

// 更新処理
void Update()
{
	bg->Update(transform2);

	if (Input::GetInstance().GetKey(DIK_W)) transform.pos.y += 0.1;
	if (Input::GetInstance().GetKey(DIK_S)) transform.pos.y -= 0.1;
	if (Input::GetInstance().GetKey(DIK_D)) transform.pos.x += 0.1;
	if (Input::GetInstance().GetKey(DIK_A)) transform.pos.x -= 0.1;

	if (Input::GetInstance().GetKey(DIK_UP))	transform.rot.x++;
	if (Input::GetInstance().GetKey(DIK_DOWN))  transform.rot.x--;
	if (Input::GetInstance().GetKey(DIK_LEFT))  transform.rot.y++;
	if (Input::GetInstance().GetKey(DIK_RIGHT)) transform.rot.y--;

	cube->Update(transform);
}

// 描画処理
void Draw()
{
	//bg->Draw();
	cube->Draw();
}

// インスタンスのdelete
void Delete()
{
	delete bg;
	delete cube;
}