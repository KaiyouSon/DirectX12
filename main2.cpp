#include "main2.h"
#include "ViewProjection.h"
#include "Image.h"
#include "Cube.h"
#include "Util.h"
#include "MathUtil.h"
#include "Input.h"

Image* bg = new Image(Vec2(WIN_WIDTH, WIN_HEIGHT));
Cube* cube = new Cube;

// �摜�̓ǂݍ���
void Load()
{
	cube->LoadGraph(L"Resources/pic.png");
	bg->LoadGraph(L"Resources/bg.png");
}

// ����������
void Initialize()
{
	cube->Initialize();
	bg->Initialize(Image::view2D);

	View::GetInstance().SetEye(Vec3(0, 0, -30));
	View::GetInstance().SetTarget(Vec3(0, 0, 0));
	View::GetInstance().SetUp(Vec3(0, 1, 0));
}

Transform transform =
{
	Vec3(0,0,0),
	Vec3(1,1,1),
	Vec3(0,0,0),
};
float playerAngle = 0;

Transform transform2 =
{
	Vec3(WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0),
	Vec3(1,1,1),
	Vec3(0,0,0),
};

// �X�V����
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

	//transform.pos.x = Input::GetInstance().GetMousePos().x;
	//transform.pos.y = Input::GetInstance().GetMousePos().y;

	cube->Update(transform);
}

// �`�揈��
void Draw3D()
{
	cube->Draw();
}

void Draw2D()
{
	bg->Draw();
}

// �C���X�^���X��delete
void Delete()
{
	delete bg;
	delete cube;
}