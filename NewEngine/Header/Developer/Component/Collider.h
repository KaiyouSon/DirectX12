#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"

class Collider : public IComponent
{
};

struct ReyCollider
{
	Vec3 startPos;
	Vec3 dirVec;

	ReyCollider() : startPos(0, 0, 0), dirVec(0, 0, 0)
	{
	}

	ReyCollider(const Vec3& startPos, const Vec3& dirVec) :startPos(startPos), dirVec(dirVec)
	{
	}
};
struct LineCollider
{
	Vec3 startPos;
	Vec3 endPos;

	LineCollider() :startPos(0, 0, 0), endPos(0, 0, 0)
	{
	}

	LineCollider(const Vec3& startPos, const Vec3& endPos) :startPos(startPos), endPos(endPos)
	{
	}
};
struct MeshCollider
{
	Vec3 centerPos;		// 中心座標
	Vec3 upperLeftPos;	// 左上座標
	Vec3 upperRightPos;	// 右上座標
	Vec3 lowerLeftPos;	// 左下座標
	Vec3 lowerRightPos;	// 左上座標
	Vec3 normal;		// 法線ベクトル

	MeshCollider() :centerPos(0, 0, 0),
		upperLeftPos(0, 0, 0), upperRightPos(0, 0, 0),
		lowerLeftPos(0, 0, 0), lowerRightPos(0, 0, 0),
		normal(0, 0, 0)
	{
	}

	MeshCollider(const Vec3& centerPos, const Vec3& scale) :
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

bool ReyHitMesh(const ReyCollider& rey, const MeshCollider& mesh);
bool LineHitMesh(const LineCollider& line, const MeshCollider& mesh);