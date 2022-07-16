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
#include "NewEngine/Header/Developer/Object/Object2D/RenderTexture.h"
#include <vector>

Sound testSound;

RenderTexture* sceneViewTexture = new RenderTexture;

void Collision();
Vec3 Vec3MulMat(Vec3 vec, Mat4 mat);

// 画像の読み込み
void Load()
{
	//LoadBasicModel();
	gameTextureList->AddTexture(LoadTexture("Resources/bg.png"), "bg");
	gameTextureList->AddTexture(LoadTexture("Resources/pic.png"), "obj");
	gameTextureList->AddTexture(LoadTexture("Resources/scope.png"), "scope");

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
}

Transform trans =
{
	{960,400,0},
	Vec3::one,
	Vec3::zero
};

static int hitType = 0;

Color color = Color::red;
static float speed = 5;
static bool isChange = false;
// 更新処理
void Update()
{
	Object3D* triangle = objManager->GetObject3D("Model");

	// 色自動に変更
	if (color.r >= 255 && color.b <= 0) { color.r = 255; color.b = 0; color.g += speed; }
	if (color.g >= 255 && color.b <= 0) { color.g = 255; color.b = 0; color.r -= speed; }
	if (color.r <= 0 && color.g >= 255) { color.r = 0; color.g = 255; color.b += speed; }
	if (color.r <= 0 && color.b >= 255) { color.r = 0; color.b = 255; color.g -= speed; }
	if (color.g <= 0 && color.b >= 255) { color.g = 0; color.b = 255; color.r += speed; }
	if (color.r >= 255 && color.g <= 0) { color.r = 255; color.g = 0; color.b -= speed; }

	triangle->SetColor(color);

	//Collision();

	if (key->GetKey(DIK_RIGHT)) trans.pos.x++;
	if (key->GetKey(DIK_LEFT)) trans.pos.x--;
	if (key->GetKey(DIK_UP)) trans.pos.y--;
	if (key->GetKey(DIK_DOWN)) trans.pos.y++;

	view->SetPos(DebugCamera::GetInstance()->GetPos());
	view->SetTarget(DebugCamera::GetInstance()->GetTarget());
	view->SetUp(DebugCamera::GetInstance()->GetUp());
	DebugCamera::GetInstance()->Update();

	//PlaySoundWave(testSound);
	//test->Update();
}

// インスタンスのdelete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	delete gameTextureList;
	delete tagList;
	ModelDataList::DestroyInstance();
	delete sceneViewTexture;
}

void Collision()
{
	if (key->GetKeyTrigger(DIK_SPACE))
	{
		if (hitType == 0) hitType = 1;
		else if (hitType == 1) hitType = 0;
	}

	Object3D* cube1 = objManager->GetObjectList()[0];
	Object3D* cube2 = objManager->GetObjectList()[1];
	Sprite* backGround = objManager->GetSpriteList()[0];
	Transform* cubeTrans = cube1->GetComponent<Transform>();
	Transform* reyTrans = cube2->GetComponent<Transform>();

	// レイ
	Rey rey =
	{
		reyTrans->pos + (Vec3::back * reyTrans->scale),
		Vec3::forward
	};

	// 線分
	Line line =
	{
		reyTrans->pos + (Vec3::back * reyTrans->scale),
		reyTrans->pos - (Vec3::back * reyTrans->scale)
	};

	// メッシュ
	Mesh mesh =
	{
		cubeTrans->pos + (Vec3::back * cubeTrans->scale),
		cubeTrans->scale
	};

	if (hitType == 0)
	{
		if (ReyHitMesh(rey, mesh))	backGround->SetisShow(true);
		else						backGround->SetisShow(false);
	}
	else
	{
		if (LineHitMesh(line, mesh)) backGround->SetisShow(true);
		else						 backGround->SetisShow(false);
	}
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