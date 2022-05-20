#pragma once
#include "MathUtil.h"

class ViewProjection
{
private:
	Vec3 pos = { 0,0,-30 };		// ���_���W
	Vec3 target = { 0,0,0 };	// �����_���W
	Vec3 up = { 0,1,0 };		// ������x�N�g��

public:
	//XMMATRIX matView;	// �r���[�ϊ��s��
	Mat4 matView;

	Mat4 matProjection2D;	// ���s���e�s��
	Mat4 matProjection3D;	// �������e�s��

public:
	void Initialize();

	void SetPos(const Vec3& pos);
	void SetTarget(const Vec3& target);
	void SetUp(const Vec3& up);

	static ViewProjection& GetInstance();
private:
	ViewProjection() = default;
	~ViewProjection() = default;

	ViewProjection(const ViewProjection&) = delete;
	ViewProjection& operator=(const ViewProjection&) = delete;
	ViewProjection(const ViewProjection&&) = delete;
	ViewProjection& operator=(const ViewProjection&&) = delete;

}typedef View;