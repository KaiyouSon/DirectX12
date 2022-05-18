#pragma once
#include "Vec2.h"
#include "Vec3.h"

// 頂点データクラス
class Vertex
{
public:
	Vec3 pos;	 // xyz座標
	Vec3 normal; // 法線ベクトル
	Vec2 uv;	 // uv座標
};

