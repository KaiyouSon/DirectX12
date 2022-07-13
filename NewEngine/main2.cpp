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
#include "NewEngine/Header/Developer/Object/Object2D/Square.h"
#include <vector>

Sound testSound;
Model barbla;

Square* square = new Square;

struct Rey
{
	Vec3 startPos;
	Vec3 dirVec;

	Rey() : startPos(0, 0, 0), dirVec(0, 0, 0)
	{
	}

	Rey(const Vec3& startPos, const Vec3& dirVec) :startPos(startPos), dirVec(dirVec)
	{
	}
};
struct Line
{
	Vec3 startPos;
	Vec3 endPos;

	Line() :startPos(0, 0, 0), endPos(0, 0, 0)
	{
	}

	Line(const Vec3& startPos, const Vec3& endPos) :startPos(startPos), endPos(endPos)
	{
	}
};
struct Mesh
{
	Vec3 centerPos;		// 中心座標
	Vec3 upperLeftPos;	// 左上座標
	Vec3 upperRightPos;	// 右上座標
	Vec3 lowerLeftPos;	// 左下座標
	Vec3 lowerRightPos;	// 左上座標
	Vec3 normal;		// 法線ベクトル

	Mesh() :centerPos(0, 0, 0),
		upperLeftPos(0, 0, 0), upperRightPos(0, 0, 0),
		lowerLeftPos(0, 0, 0), lowerRightPos(0, 0, 0),
		normal(0, 0, 0)
	{
	}

	Mesh(const Vec3& centerPos, const Vec3& scale) :
		centerPos(centerPos),
		upperLeftPos(centerPos.x - scale.x, centerPos.y + scale.y, centerPos.z),
		upperRightPos(centerPos.x + scale.x, centerPos.y + scale.y, centerPos.z),
		lowerLeftPos(centerPos.x - scale.x, centerPos.y - scale.y, centerPos.z),
		lowerRightPos(centerPos.x + scale.x, centerPos.y - scale.y, centerPos.z),
		normal(Vec3::Cross(
			(lowerRightPos - lowerLeftPos).Normalized(),
			(upperLeftPos - lowerLeftPos).Normalized()))
	{
	}
};

bool ReyHitMesh(const Rey& rey, const Mesh& mesh);
bool LineHitMesh(const Line& line, const Mesh& mesh);
void Collision();
Vec3 Vec3MulMat(Vec3 vec, Mat4 mat);

// 画像の読み込み
void Load()
{
	LoadBasicModel();
	gameTextureList->AddTexture(LoadTexture("Resources/bg.png"), "bg");
	gameTextureList->AddTexture(LoadTexture("Resources/pic.png"), "obj");
	gameTextureList->AddTexture(LoadTexture("Resources/scope.png"), "scope");

	testSound = LoadSoundWave("Resources/title_bgm.wav");

	//barbla = LoadModel("Resources/barbla.obj");

}

// 初期化処理
void Initialize()
{
	view->SetPos(Vec3(0, 0, -50));
	view->SetTarget(Vec3::zero);
	view->SetUp(Vec3::up);

	DebugCamera::GetInstance()->Initialize();

	square->Initialize(Square::view2D, { WIN_HALF_WIDTH,WIN_HALF_HEIGHT });
}

Transform trans =
{
	{WIN_HALF_WIDTH,WIN_HALF_HEIGHT,0},
	Vec3::one,
	Vec3::zero
};

static int hitType = 0;

// 更新処理
void Update()
{
	if (key->GetKeyTrigger(DIK_SPACE))
	{
		if (hitType == 0) hitType = 1;
		else if (hitType == 1) hitType = 0;
	}

	Object3D* cube1 = ObjectManager::GetInstance()->GetObjectList()[0];
	Object3D* cube2 = ObjectManager::GetInstance()->GetObjectList()[1];
	Sprite* backGround = ObjectManager::GetInstance()->GetSpriteList()[0];
	Sprite* scope = ObjectManager::GetInstance()->GetSpriteList()[1];
	Transform* cubeTrans = cube1->GetComponent<Transform>();
	Transform* scopeTrans = scope->GetComponent<Transform>();

	Mat4 viewportMat = MathUtil::ConvertViewportMat(*viewport);	// ビューポート行列
	Mat4 viewportInvMat = Mat4::Inverse(viewportMat);			// ビューポート逆行列
	Mat4 projectionInvMat = Mat4::Inverse(view->matProjection2D);
	Mat4 viewInvMat = Mat4::Inverse(view->matView);

	// Test1
	//Mat4 scopeMat = scope->GetFinalMat();
	//Vec3 reyPos = { scopeMat.mat[3][0],scopeMat.mat[3][1], scopeMat.mat[3][2] };
	//reyPos = Vec3MulMat(reyPos, viewportInvMat);
	//reyPos = Vec3MulMat(reyPos, projectionInvMat);
	//reyPos = Vec3MulMat(reyPos, viewInvMat);

	// Test2
	Mat4 scopeMat = scope->GetFinalMat();
	scopeMat *= viewportInvMat;
	scopeMat *= projectionInvMat;
	scopeMat *= viewInvMat;
	Vec3 reyPos = { scopeMat.mat[3][0],scopeMat.mat[3][1], scopeMat.mat[3][2] };

	//Rey rey =
	//{
	//	Vec3(reyVec.x,reyVec.y,view->GetNearZ()),
	//	Vec3(reyVec.x,reyVec.y,view->GetFarZ())
	//};

	//Mesh mesh =
	//{
	//	cubeTrans->pos + (Vec3::back * cubeTrans->scale),
	//	cubeTrans->scale
	//};

	//if (ReyHitMesh(rey, mesh))	backGround->SetisShow(true);
	//else						backGround->SetisShow(false);

	//Collision();

	square->Update(trans);

	view->SetPos(DebugCamera::GetInstance()->GetPos());
	view->SetTarget(DebugCamera::GetInstance()->GetTarget());
	view->SetUp(DebugCamera::GetInstance()->GetUp());
	DebugCamera::GetInstance()->Update();

	//PlaySoundWave(testSound);

	//test->Update();
}

void Draw2D()
{
	square->Draw();
}

// インスタンスのdelete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	delete gameTextureList;
	delete tagList;

	delete square;
}

void Collision()
{
	Object3D* cube1 = ObjectManager::GetInstance()->GetObjectList()[0];
	Object3D* cube2 = ObjectManager::GetInstance()->GetObjectList()[1];
	Sprite* backGround = ObjectManager::GetInstance()->GetSpriteList()[0];
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
bool ReyHitMesh(const Rey& rey, const Mesh& mesh)
{
	float dis1 = Vec3::Distance(rey.startPos, Vec3::zero);	// レイの始点と原点の距離
	float dis2 = Vec3::Distance(mesh.centerPos, Vec3::zero);	// メッシュの中心座標と原点の距離
	float dist = dis1 - dis2;	// レイの始点とメッシュ距離

	// メッシュの法線とレイのベクトルでcosθを求める
	float cosRadius = Vec3::Dot(mesh.normal * -1, rey.dirVec.Normalized());

	// 当たった点
	Vec3 inter = rey.startPos + rey.dirVec.Normalized() * dist;

	if (inter.x >= mesh.lowerLeftPos.x && inter.x <= mesh.lowerRightPos.x &&
		inter.y >= mesh.lowerLeftPos.y && inter.y <= mesh.upperLeftPos.y)
		return true;

	return false;
}
bool LineHitMesh(const Line& line, const Mesh& mesh)
{
	Vec3 v1 = line.startPos - mesh.centerPos;
	Vec3 v2 = line.endPos - mesh.centerPos;
	Vec3 v3 = v1 + v2;

	if (Vec3::Dot(v1, mesh.normal * Vec3::Dot(v2, mesh.normal)) <= 0)
	{
		if (v1.x >= mesh.lowerLeftPos.x && v1.x <= mesh.lowerRightPos.x &&
			v1.y >= mesh.lowerLeftPos.y && v1.y <= mesh.upperLeftPos.y)
		{
			return true;
		}
		if (v2.x >= mesh.lowerLeftPos.x && v2.x <= mesh.lowerRightPos.x &&
			v2.y >= mesh.lowerLeftPos.y && v2.y <= mesh.upperLeftPos.y)
		{
			return true;
		}

	}
	return false;
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