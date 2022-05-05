#pragma once
#include "ConstantBuffer.h"

#include <DirectXMath.h>
using namespace DirectX;

class Sprite
{

private:
	int vbArraySize;	// 頂点データの要素数
	int ibArraySize;	// インデックスデータの要素数
public:
	Sprite();
	void Initialize();
	void DrawBox(XMFLOAT4 color);
	void DrawGraph();
};