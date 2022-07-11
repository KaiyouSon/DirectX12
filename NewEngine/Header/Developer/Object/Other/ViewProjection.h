#pragma once
#include "NewEngine/Header/Developer/Math/MathUtil.h"

class ViewProjection
{
private:
	Vec3 pos = { 0,0,-30 };		// 視点座標
	Vec3 target = { 0,0,0 };	// 注視点座標
	Vec3 up = { 0,1,0 };		// 上方向ベクトル
	float nearZ;
	float farZ;

public:
	Mat4 matView;			// ビュー変換行列
	Mat4 matProjection2D;	// 平行投影行列
	Mat4 matProjection3D;	// 透視投影行列

public:
	void Initialize();
	void SetPos(const Vec3& pos);
	void SetTarget(const Vec3& target);
	void SetUp(const Vec3& up);

	Vec3 GetPos();
	Vec3 GetTarget();
	Vec3 GetUp();

	float GetNearZ();
	float GetFarZ();

	static ViewProjection* GetInstance();
	static void DestroyInstance();
private:
	ViewProjection() = default;
	~ViewProjection() = default;

	ViewProjection(const ViewProjection&) = delete;
	ViewProjection& operator=(const ViewProjection&) = delete;
	ViewProjection(const ViewProjection&&) = delete;
	ViewProjection& operator=(const ViewProjection&&) = delete;

}typedef View;

extern View* view;