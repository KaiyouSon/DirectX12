#pragma once
#include "NewEngine/Header/Developer/Math/Vec3.h"
class Quaternion
{
public:
	float x, y, z, w;

	// コンストラクタ
	Quaternion();
	Quaternion(float x, float y, float z, float w);

	static Quaternion AngleAxis(const float& angle, const Vec3& axis);
};
