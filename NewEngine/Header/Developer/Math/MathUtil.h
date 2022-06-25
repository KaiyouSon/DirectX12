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

	// 弧度法から度数法に変換する関数
	static float Angle(float radian);
	// 度数法から弧度法に変換する関数
	static float Radian(float angle);

	// 絶対値を返す関数
	static float Absolut(float num);
};