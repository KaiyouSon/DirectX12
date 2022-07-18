#pragma once
#include "NewEngine/Header/Developer/Math/Vec3.h"

class Mat4
{
public:
	float mat[4][4] = {};

	Mat4();
	Mat4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);

	static Mat4 Zero();		// �[���s���Ԃ��֐�
	static Mat4 Identity();	// �P�ʍs���Ԃ��֐�
	static Mat4 Inverse(const Mat4& mat);	// �t�s���Ԃ��֐�

	// �s����f�o�b�N�e�N�X�g�Ƃ��ĕ\������
	static void PrintMat(float x, float y, const Mat4& mat, const char* str = "mat");

	// �P�����Z�q�I�[�o�[���[�h
	Mat4 operator*(const Mat4& other) const;
	Mat4 operator*(const float& num);

	// ������Z�q�I�[�o�[���[�h
	Mat4& operator*=(const Mat4& other);
};