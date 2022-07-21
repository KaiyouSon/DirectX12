#include "NewEngine/main2.h"
#include "NewEngine/Header/Developer/Util/Util.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"
#include "NewEngine/Header/Developer/Input/InputManager.h"
#include "NewEngine/Header/Developer/Debug/DebugManager.h"
#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Object/Other/ObjectManager.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Developer/Component/Tag.h"
#include "NewEngine/Header/Developer/Debug/DebugCamera.h"
#include "NewEngine/Header/Developer/Sound.h"
#include "NewEngine/Header/Render/Viewport.h"
#include <vector>

Sound testSound;

Vec3 Vec3MulMat(Vec3 vec, Mat4 mat);
static const int maxLine = 21;
static float lineYAxis = -10;
Line* xLine = new Line[maxLine];
Line* zLine = new Line[maxLine];

// 画像の読み込み
void Load()
{
	testSound = LoadSoundWave("Resources/title_bgm.wav");
}

// 初期化処理
void Initialize()
{
	view->SetPos(Vec3(0, 0, -50));
	view->SetTarget(Vec3::zero);
	view->SetUp(Vec3::up);

	DebugCamera::GetInstance()->Initialize();

	sceneViewTexture->Initialize({ 960,540 });
	for (int i = 0; i < maxLine; i++)
	{
		xLine[i].Initialize({ -10.0f,lineYAxis,-10.0f + i }, { 10.0f,lineYAxis,-10.0f + i });
		zLine[i].Initialize({ -10.0f + i,lineYAxis,-10.0f }, { -10.0f + i,lineYAxis,10.0f });
	}
}

static int hitType = 0;
Color color = Color::red;
static float speed = 5;
static bool isChange = false;
// 更新処理
void Update()
{
	GameObject* triangle = objManager->GetGameObject("Triangle");

	// 色自動に変更
	if (color.r >= 255 && color.b <= 0) { color.r = 255; color.b = 0; color.g += speed; }
	if (color.g >= 255 && color.b <= 0) { color.g = 255; color.b = 0; color.r -= speed; }
	if (color.r <= 0 && color.g >= 255) { color.r = 0; color.g = 255; color.b += speed; }
	if (color.r <= 0 && color.b >= 255) { color.r = 0; color.b = 255; color.g -= speed; }
	if (color.g <= 0 && color.b >= 255) { color.g = 0; color.b = 255; color.r += speed; }
	if (color.r >= 255 && color.g <= 0) { color.r = 255; color.g = 0; color.b -= speed; }
	if (color.a <= 0) isChange = true; if (color.a >= 255) isChange = false;
	isChange ? color.a++ : color.a--;

	triangle->SetColor(color);

	//sceneViewTexture->GetComponent<Transform>()->pos.x = WIN_HALF_WIDTH;
	//sceneViewTexture->GetComponent<Transform>()->pos.y = WIN_HALF_HEIGHT;
	sceneViewTexture->Update();

	view->SetPos(DebugCamera::GetInstance()->GetPos());
	view->SetTarget(DebugCamera::GetInstance()->GetTarget());
	view->SetUp(DebugCamera::GetInstance()->GetUp());
	DebugCamera::GetInstance()->Update();

	for (int i = 0; i < maxLine; i++)
	{
		xLine[i].Update();
		zLine[i].Update();

		xLine[i].SetColor(Color::red);
		zLine[i].SetColor(Color::blue);
	}
	//PlaySoundWave(testSound);
}

void Draw2D()
{
	//sceneViewTexture->Draw();
}

void Draw3D()
{
}

void DrawLine()
{
	for (int i = 0; i < maxLine; i++)
	{
		xLine[i].Draw();
		zLine[i].Draw();
	}
}

// インスタンスのdelete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	delete[] xLine;
	delete[] zLine;
}

Vec3 Vec3MulMat(Vec3 vec, Mat4 mat)
{
	Vec4 tmpVec = { vec.x,vec.y,vec.z,1 };

	return
	{
		mat.mat[0][0] * tmpVec.x + mat.mat[0][1] * tmpVec.y + mat.mat[0][2] * tmpVec.z + mat.mat[0][3] * tmpVec.w,
		mat.mat[1][0] * tmpVec.x + mat.mat[1][1] * tmpVec.y + mat.mat[1][2] * tmpVec.z + mat.mat[1][3] * tmpVec.w,
		mat.mat[2][0] * tmpVec.x + mat.mat[2][1] * tmpVec.y + mat.mat[2][2] * tmpVec.z + mat.mat[2][3] * tmpVec.w,
		//mat.mat[3][0] * tmpVec.x * mat.mat[3][1] * tmpVec.y * mat.mat[3][2] * tmpVec.z * mat.mat[3][3] * tmpVec.w
	};

}
Vec3 Vec3Transform(Vec3 vec, Mat4 mat)
{
	float w = (vec.x * mat.mat[0][3]) + (vec.y * mat.mat[1][3]) + (vec.z * mat.mat[2][3]) + (mat.mat[3][3]);

	return
	{
		(vec.x * mat.mat[0][0]) + (vec.y * mat.mat[1][0]) + (vec.z * mat.mat[2][0]) + (mat.mat[3][0]) / w,
		(vec.x * mat.mat[0][1]) + (vec.y * mat.mat[1][1]) + (vec.z * mat.mat[2][1]) + (mat.mat[3][1]) / w,
		(vec.x * mat.mat[0][2]) + (vec.y * mat.mat[1][2]) + (vec.z * mat.mat[2][2]) + (mat.mat[3][2]) / w,
	};
}