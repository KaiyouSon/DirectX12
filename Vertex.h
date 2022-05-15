#pragma once
#include <DirectXMath.h>
using namespace DirectX;

// 頂点データクラス
class Vertex
{
public:
	XMFLOAT3 pos;	 // xyz座標
	XMFLOAT3 normal; // 法線ベクトル
	XMFLOAT2 uv;	 // uv座標
};

