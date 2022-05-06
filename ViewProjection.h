#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
private:
	XMFLOAT3 eye;	// 視点座標
	XMFLOAT3 target;	// 注視点座標
	XMFLOAT3 up;		// 上方向ベクトル

public:
	// ビュー変換行列
	XMMATRIX matView;

	// 透視投影行列の計算
	XMMATRIX matProjection;

public:
	ViewProjection();
	void Initialize();

	void SetEye(const XMFLOAT3& eye);
	void SetTarget(const XMFLOAT3& target);
	void SetUp(const XMFLOAT3& up);
};