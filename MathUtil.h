#pragma once
#include <math.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

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