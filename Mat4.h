#pragma once
#include "Vec3.h"

class Mat4
{
public:
	float mat[4][4];

	Mat4();
	Mat4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);

	static Mat4 Identity();	// �P�ʍs���Ԃ��֐�

	static Mat4 Scale(Vec3 scale);		// �X�P�[�����O�s���Ԃ��֐�
	static Mat4 RotateX(float angle);	// ��]�s�񂘎���Ԃ��֐�
	static Mat4 RotateY(float angle);	// ��]�s�񂙎���Ԃ��֐�
	static Mat4 RotateZ(float angle);	// ��]�s�񂚎���Ԃ��֐�
	static Mat4 Translate(Vec3 pos);	// ���s�ړ���Ԃ��֐�
};