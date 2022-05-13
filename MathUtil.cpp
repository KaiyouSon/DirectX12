#include "MathUtil.h"

float Angle(float radian)
{
	return radian * 360 / (2 * PI);
}

float Radian(float angle)
{
	return angle * (2 * PI) / 360;
}