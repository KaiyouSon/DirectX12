#pragma once
#include "Mat4.h"
#include "Vec3.h"

class Transform
{
public:
	Vec3 pos = { 0,0,0 };	// ���W
	Vec3 scale = { 1,1,1 };	// �X�P�[��
	Vec3 rot = { 0,0,0 };	// ��]

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
	//Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot);
	Transform(Vec3 pos, Vec3 scale, Vec3 rot);
	void Update();
};

