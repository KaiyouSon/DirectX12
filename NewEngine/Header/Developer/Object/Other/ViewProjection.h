#pragma once
#include "NewEngine/Header/Developer/Math/MathUtil.h"

class ViewProjection
{
private:
	Vec3 pos = { 0,0,-30 };		// ���_���W
	Vec3 target = { 0,0,0 };	// �����_���W
	Vec3 up = { 0,1,0 };		// ������x�N�g��
	float nearZ;
	float farZ;

public:
	Mat4 matView;			// �r���[�ϊ��s��
	Mat4 matProjection2D;	// ���s���e�s��
	Mat4 matProjection3D;	// �������e�s��

public:
	void Initialize();
	void SetPos(const Vec3& pos);
	void SetTarget(const Vec3& target);
	void SetUp(const Vec3& up);

	Vec3 GetPos();
	Vec3 GetTarget();
	Vec3 GetUp();

	float GetNearZ();
	float GetFarZ();

	static ViewProjection* GetInstance();
	static void DestroyInstance();
private:
	ViewProjection() = default;
	~ViewProjection() = default;

	ViewProjection(const ViewProjection&) = delete;
	ViewProjection& operator=(const ViewProjection&) = delete;
	ViewProjection(const ViewProjection&&) = delete;
	ViewProjection& operator=(const ViewProjection&&) = delete;

}typedef View;

extern View* view;