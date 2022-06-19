#pragma once
#include "Header/MathUtil.h"

class Transform
{
public:
	Vec3 pos;	// ���W
	Vec3 scale;	// �X�P�[��
	Vec3 rot;	// ��]

	// ���[���h�ϊ��s��
	Mat4 matWorld = Mat4::Identity();
private:
	// �X�P�[���s��
	Mat4 matScale = Mat4::Identity();
	// ��]�s��
	Mat4 matRot = Mat4::Identity();
	// ���s�ړ��s��
	Mat4 matTrans = Mat4::Identity();
public:
	Transform();
	Transform(Vec3 pos, Vec3 scale, Vec3 rot);
	void Update();
};

