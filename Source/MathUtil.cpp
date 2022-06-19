#include "Header/MathUtil.h"

const float MathUtil::PI = 3.141592f;

float MathUtil::Angle(float radian)
{
	return radian * 360 / (2 * PI);
}

float MathUtil::Radian(float angle)
{
	return angle * (2 * PI) / 360;
}

float MathUtil::Absolut(float num)
{
	if (num >= 0) return num;
	else          return num * -1;
}
