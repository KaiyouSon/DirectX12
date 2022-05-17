#pragma once
#include <DirectXMath.h>
using namespace DirectX;
#include "Mat4.h"

class Transform
{
public:
	XMFLOAT3 pos = { 0,0,0 };	// 座標
	XMFLOAT3 scale = { 1,1,1 };	// スケール
	XMFLOAT3 rot = { 0,0,0 };	// 回転

	// ワールド変換行列
	//XMMATRIX matWorld;
	Mat4 matWorld;

public:
	Transform();
	Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);
	void Update();
};

