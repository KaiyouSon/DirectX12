#pragma once
#include <math.h>
#include "Header/Vec2.h"
#include "Header/Vec3.h"
#include "Header/Vec4.h"
#include "Header/Mat4.h"

class MathUtil
{
public:
	static const float PI;

	// �ʓx�@����x���@�ɕϊ�����֐�
	static float Angle(float radian);
	// �x���@����ʓx�@�ɕϊ�����֐�
	static float Radian(float angle);

	// ��Βl��Ԃ��֐�
	static float Absolut(float num);
};