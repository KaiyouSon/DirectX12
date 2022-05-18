#pragma once
#include "Mat4.h"
#include "Vec3.h"

class Transform
{
public:
	Vec3 pos = { 0,0,0 };	// 座標
	Vec3 scale = { 1,1,1 };	// スケール
	Vec3 rot = { 0,0,0 };	// 回転

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
	//Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);
	Transform(Vec3 pos, Vec3 scale, Vec3 rot);
	void Update();
};

