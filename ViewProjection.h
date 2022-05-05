#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
public:
	// ビュー変換行列
	XMMATRIX matView;

	// 透視投影行列の計算
	XMMATRIX matProjection;

public:
	void Initialize();
};