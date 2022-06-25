#pragma once
#include <math.h>
#include "NewEngine/Header/Developer/Math/Vec2.h"
#include "NewEngine/Header/Developer/Math/Vec3.h"
#include "NewEngine/Header/Developer/Math/Vec4.h"
#include "NewEngine/Header/Developer/Math/Mat4.h"

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