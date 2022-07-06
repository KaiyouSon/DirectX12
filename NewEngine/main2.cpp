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
#include "ImGUI/imgui.h"
#include<vector>

Sound testSound;
Model barbla;

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
	Vec3 centerPos;		// ���S���W
	Vec3 upperLeftPos;	// ������W
	Vec3 upperRightPos;	// �E����W
	Vec3 lowerLeftPos;	// �������W
	Vec3 lowerRightPos;	// ������W
	Vec3 normal;		// �@���x�N�g��

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

// �摜�̓ǂݍ���
void Load()
{
	LoadBasicModel();
	gameTextureList->PushToTextureList(LoadTexture("Resources/bg.png"), "bg");
	gameTextureList->PushToTextureList(LoadTexture("Resources/pic.png"), "obj");
	gameTextureList->PushToTextureList(LoadTexture("Resources/scope.png"), "scope");

	testSound = LoadSoundWave("Resources/title_bgm.wav");

	//barbla = LoadModel("Resources/barbla.obj");
}

// ����������
void Initialize()
{
	view->SetPos(Vec3(0, 0, -50));
	view->SetTarget(Vec3::zero);
	view->SetUp(Vec3::up);

	DebugCamera::GetInstance()->Initialize();

	//test->Initialize();
}

Transform trans;
static int hitType = 0;

// �X�V����
void Update()
{
	if (key->GetKeyTrigger(DIK_SPACE))
	{
		if (hitType == 0) hitType = 1;
		else if (hitType == 1) hitType = 0;
	}

	Collision();

	view->SetPos(DebugCamera::GetInstance()->GetPos());
	view->SetTarget(DebugCamera::GetInstance()->GetTarget());
	view->SetUp(DebugCamera::GetInstance()->GetUp());
	DebugCamera::GetInstance()->Update();

	//PlaySoundWave(testSound);

	//test->Update();
}

// �C���X�^���X��delete
void Destroy()
{
	UnLoadSoundWave(&testSound);
	delete gameTextureList;
	delete tagList;
}

void Collision()
{
	Object3D* cube1 = ObjectManager::GetInstance()->GetObjectList()[0];
	Object3D* cube2 = ObjectManager::GetInstance()->GetObjectList()[1];
	Sprite* backGround = ObjectManager::GetInstance()->GetSpriteList()[1];
	Transform* cubeTrans = cube1->GetComponent<Transform>("Transform");
	Transform* reyTrans = cube2->GetComponent<Transform>("Transform");

	// ���C
	Rey rey =
	{
		reyTrans->pos + (Vec3::back * reyTrans->scale),
		Vec3::forward
	};

	// ����
	Line line =
	{
		reyTrans->pos + (Vec3::back * reyTrans->scale),
		reyTrans->pos - (Vec3::back * reyTrans->scale)
	};

	// ���b�V��
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
	float dis1 = Vec3::Distance(rey.startPos, Vec3::zero);	// ���C�̎n�_�ƌ��_�̋���
	float dis2 = Vec3::Distance(mesh.centerPos, Vec3::zero);	// ���b�V���̒��S���W�ƌ��_�̋���
	float dist = dis1 - dis2;	// ���C�̎n�_�ƃ��b�V������

	// ���b�V���̖@���ƃ��C�̃x�N�g����cos�Ƃ����߂�
	float cosRadius = Vec3::Dot(mesh.normal * -1, rey.dirVec.Normalized());

	// ���������_
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