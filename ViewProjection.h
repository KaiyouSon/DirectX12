#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
private:
	XMFLOAT3 eye = { 0,0,-30 };		// ���_���W
	XMFLOAT3 target = { 0,0,0 };	// �����_���W
	XMFLOAT3 up = { 0,1,0 };		// ������x�N�g��

public:
	XMMATRIX matView;	// �r���[�ϊ��s��

	XMMATRIX matProjection2D;	// ���s���e�s��
	XMMATRIX matProjection3D;	// �������e�s��

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