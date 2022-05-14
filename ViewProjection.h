#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
private:
	XMFLOAT3 eye = { 0,0,-30 };		// 視点座標
	XMFLOAT3 target = { 0,0,0 };	// 注視点座標
	XMFLOAT3 up = { 0,1,0 };		// 上方向ベクトル

public:
	XMMATRIX matView;	// ビュー変換行列

	XMMATRIX matProjection2D;	// 平行投影行列
	XMMATRIX matProjection3D;	// 透視投影行列

public:
	void Initialize();

	void SetEye(const XMFLOAT3& eye);
	void SetTarget(const XMFLOAT3& target);
	void SetUp(const XMFLOAT3& up);

	static ViewProjection& GetInstance();

private:
	ViewProjection() = default;
	~ViewProjection() = default;

	ViewProjection(const ViewProjection&) = delete;
	ViewProjection& operator=(const ViewProjection&) = delete;
	ViewProjection(const ViewProjection&&) = delete;
	ViewProjection& operator=(const ViewProjection&&) = delete;

}typedef View;