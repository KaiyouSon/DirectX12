#pragma once
#include <math.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

const float PI = 3.141592f;

/// <summary>
/// 弧度法から度数法に変換する関数
/// </summary>
float Angle(float radian);

/// <summary>
/// 度数法から弧度法に変換する関数
/// </summary>
float Radian(float angle);