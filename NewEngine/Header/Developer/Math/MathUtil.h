#pragma once
#include <math.h>
#include "NewEngine/Header/Developer/Math/Vec2.h"
#include "NewEngine/Header/Developer/Math/Vec3.h"
#include "NewEngine/Header/Developer/Math/Vec4.h"
#include "NewEngine/Header/Developer/Math/Mat4.h"
#include "NewEngine/Header/Developer/Math/Quaternion.h"

class MathUtil
{
public:
	static const float PI;

	// ��Βl��Ԃ��֐�
	static float Absolut(float num);

	// �ʓx�@����x���@�ɕϊ�����֐�
	static float Angle(float radian);
	static Vec2 Angle(Vec2 radian);
	static Vec3 Angle(Vec3 radian);
	// �x���@����ʓx�@�ɕϊ�����֐�
	static float Radian(float angle);
	static Vec2 Radian(Vec2 angle);
	static Vec3 Radian(Vec3 angle);

	Vec2 ConvertVec3ToVec2(Vec3 vec);	// 3�����x�N�g����2�����x�N�g���ɕϊ�
	Vec3 ConvertVec2ToVec3(Vec2 vec);	// 2�����x�N�g����3�����x�N�g���ɕϊ�

	static Mat4 ConvertQuaternionToRotationMat(Quaternion q);	// �N�H�[�^�j�I������]�s��ɕς���

	static Mat4 ConvertScalingMat(Vec3 scale);		// �X�P�[�����O�s���Ԃ��֐�
	static Mat4 ConvertRotationXAxisMat(float angle);	// ��]�s�񂘎���Ԃ��֐�
	static Mat4 ConvertRotationYAxisMat(float angle);	// ��]�s�񂙎���Ԃ��֐�
	static Mat4 ConvertRotationZAxisMat(float angle);	// ��]�s�񂚎���Ԃ��֐�
	static Mat4 ConvertTranslationMat(const Vec3& pos);	// ���s�ړ���Ԃ��֐�

	static Mat4 ConvertViewProjectionMat(const Vec3& pos, const Vec3& target, const Vec3& up);			// �r���[�ϊ�
	static Mat4 ConvertPerspectiveProjectionMat(float fovAngle, float aspect, float nearZ, float farZ);	// �����ˉe�ϊ�
	static Mat4 ConvertOrthoGrphicProjectionMat(int WIN_WIDTH, int WIN_HEIGHT);							// ���s�ˉe�ϊ�
};