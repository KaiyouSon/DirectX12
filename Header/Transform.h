#pragma once
#include "Header/MathUtil.h"

class Transform
{
public:
	Vec3 pos;	// 座標
	Vec3 scale;	// スケール
	Vec3 rot;	// 回転

	// ワールド変換行列
	Mat4 matWorld = Mat4::Identity();
private:
	// スケール行列
	Mat4 matScale = Mat4::Identity();
	// 回転行列
	Mat4 matRot = Mat4::Identity();
	// 平行移動行列
	Mat4 matTrans = Mat4::Identity();
public:
	Transform();
	Transform(Vec3 pos, Vec3 scale, Vec3 rot);
	void Update();
};

