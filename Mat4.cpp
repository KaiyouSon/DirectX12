#include "Mat4.h"
#include "MathUtil.h"
#include <math.h>

Mat4::Mat4() :
	mat{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0 }
{
}

Mat4::Mat4(
	float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33) :
	mat{
		_00,_01,_02,_03,
		_10,_11,_12,_13,
		_20,_21,_22,_23,
		_30,_31,_32,_33 }
{
}

Mat4 Mat4::Identity()
{
	return
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
}

Mat4 Mat4::Scale(Vec3 scale)
{
	return
	{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1
	};
}

Mat4 Mat4::RotateX(float angle)
{
	return
	{
		1,0,0,0,
		0,cosf(Radian(angle)),-sinf(Radian(angle)),0,
		0,sinf(Radian(angle)), cosf(Radian(angle)),0,
		0,0,0,1
	};
}

Mat4 Mat4::RotateY(float angle)
{
	return
	{
		 cosf(Radian(angle)),0,sinf(Radian(angle)),0,
		0,1,0,0,
		-sinf(Radian(angle)),0,cosf(Radian(angle)),0,
		0,0,0,1
	};
}

Mat4 Mat4::RotateZ(float angle)
{
	return
	{
		cosf(Radian(angle)),-sinf(Radian(angle)),0,0,
		sinf(Radian(angle)), cosf(Radian(angle)),0,0,
		0,0,1,0,
		0,0,0,1
	};
}

Mat4 Mat4::Translate(Vec3 pos)
{
	return
	{
		1,0,0,pos.x,
		0,1,0,pos.y,
		0,0,1,pos.z,
		0,0,0,1
	};
}