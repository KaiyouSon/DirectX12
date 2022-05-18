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

Mat4 Mat4::Zero()
{
	return
	{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};
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
		0, cosf(Radian(angle)),sinf(Radian(angle)),0,
		0,-sinf(Radian(angle)),cosf(Radian(angle)),0,
		0,0,0,1
	};
}

Mat4 Mat4::RotateY(float angle)
{
	return
	{
		cosf(Radian(angle)),0,-sinf(Radian(angle)),0,
		0,1,0,0,
		sinf(Radian(angle)),0, cosf(Radian(angle)),0,
		0,0,0,1
	};
}

Mat4 Mat4::RotateZ(float angle)
{
	return
	{
		 cosf(Radian(angle)),sinf(Radian(angle)),0,0,
		-sinf(Radian(angle)),cosf(Radian(angle)),0,0,
		0,0,1,0,
		0,0,0,1
	};
}

Mat4 Mat4::Translate(const Vec3& pos)
{
	return
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		pos.x,pos.y,pos.z,1
	};
}

Mat4 Mat4::ViewConversion(const Vec3& pos, const Vec3& target, const Vec3& up)
{
	// 単位行列で初期化
	Mat4 view = Mat4::Identity();

	// ｚ軸
	Vec3 zAxis = target - pos;
	view.mat[2][0] = zAxis.Normalized().x;
	view.mat[2][1] = zAxis.Normalized().y;
	view.mat[2][2] = zAxis.Normalized().z;

	// ｘ軸
	Vec3 xAxis = Vec3::Cross(up, zAxis);
	view.mat[0][0] = xAxis.Normalized().x;
	view.mat[0][1] = xAxis.Normalized().y;
	view.mat[0][2] = xAxis.Normalized().z;

	// ｙ軸
	Vec3 yAxis = Vec3::Cross(zAxis, xAxis);
	view.mat[1][0] = yAxis.Normalized().x;
	view.mat[1][1] = yAxis.Normalized().y;
	view.mat[1][2] = yAxis.Normalized().z;

	// 平行移動
	view.mat[3][0] = Vec3::Dot(pos, xAxis.Normalized());
	view.mat[3][1] = Vec3::Dot(pos, yAxis.Normalized());
	view.mat[3][2] = -Vec3::Dot(pos, zAxis.Normalized());

	return view;
}

Mat4 Mat4::PerspectiveConversion(float fovAngle, float aspect, float nearZ, float farZ)
{
	// 単位行列で初期化
	Mat4 perspective = Mat4::Zero();

	float scaleY = 1 / tanf(fovAngle / 2);
	float scaleX = 1 / tanf(fovAngle / 2) / aspect;
	float scaleZ = 1 / (farZ - nearZ) * farZ;
	float TransZ = -nearZ / (farZ - nearZ) * farZ;

	perspective.mat[1][1] = scaleY;
	perspective.mat[0][0] = scaleX;
	perspective.mat[2][2] = scaleZ;
	perspective.mat[3][2] = TransZ;
	perspective.mat[2][3] = 1;

	return perspective;
}

Mat4 Mat4::ParallelConversion(int WIN_WIDTH, int WIN_HEIGHT)
{
	return
	{
		2 / (float)WIN_WIDTH,0,0,0,
		0,-2 / (float)WIN_HEIGHT,0,0,
		0,0,1,0,
		-1,1,0,1
	};
}


Mat4 Mat4::operator*(const Mat4& other) const
{
	return {
		//	一行目
		mat[0][0] * other.mat[0][0] + mat[0][1] * other.mat[1][0] +
		mat[0][2] * other.mat[2][0] + mat[0][3] * other.mat[3][0],

		mat[0][0] * other.mat[0][1] + mat[0][1] * other.mat[1][1] +
		mat[0][2] * other.mat[2][1] + mat[0][3] * other.mat[3][1],

		mat[0][0] * other.mat[0][2] + mat[0][1] * other.mat[1][2] +
		mat[0][2] * other.mat[2][2] + mat[0][3] * other.mat[3][2],

		mat[0][0] * other.mat[0][3] + mat[0][1] * other.mat[1][3] +
		mat[0][2] * other.mat[2][3] + mat[0][3] * other.mat[3][3],

		// 二行目
		mat[1][0] * other.mat[0][0] + mat[1][1] * other.mat[1][0] +
		mat[1][2] * other.mat[2][0] + mat[1][3] * other.mat[3][0],

		mat[1][0] * other.mat[0][1] + mat[1][1] * other.mat[1][1] +
		mat[1][2] * other.mat[2][1] + mat[1][3] * other.mat[3][1],

		mat[1][0] * other.mat[0][2] + mat[1][1] * other.mat[1][2] +
		mat[1][2] * other.mat[2][2] + mat[1][3] * other.mat[3][2],

		mat[1][0] * other.mat[0][3] + mat[1][1] * other.mat[1][3] +
		mat[1][2] * other.mat[2][3] + mat[1][3] * other.mat[3][3],

		// 三行目
		mat[2][0] * other.mat[0][0] + mat[2][1] * other.mat[1][0] +
		mat[2][2] * other.mat[2][0] + mat[2][3] * other.mat[3][0],

		mat[2][0] * other.mat[0][1] + mat[2][1] * other.mat[1][1] +
		mat[2][2] * other.mat[2][1] + mat[2][3] * other.mat[3][1],

		mat[2][0] * other.mat[0][2] + mat[2][1] * other.mat[1][2] +
		mat[2][2] * other.mat[2][2] + mat[2][3] * other.mat[3][2],

		mat[2][0] * other.mat[0][3] + mat[2][1] * other.mat[1][3] +
		mat[2][2] * other.mat[2][3] + mat[2][3] * other.mat[3][3],

		// 四行目
		mat[3][0] * other.mat[0][0] + mat[3][1] * other.mat[1][0] +
		mat[3][2] * other.mat[2][0] + mat[3][3] * other.mat[3][0],

		mat[3][0] * other.mat[0][1] + mat[3][1] * other.mat[1][1] +
		mat[3][2] * other.mat[2][1] + mat[3][3] * other.mat[3][1],

		mat[3][0] * other.mat[0][2] + mat[3][1] * other.mat[1][2] +
		mat[3][2] * other.mat[2][2] + mat[3][3] * other.mat[3][2],

		mat[3][0] * other.mat[0][3] + mat[3][1] * other.mat[1][3] +
		mat[3][2] * other.mat[2][3] + mat[3][3] * other.mat[3][3],
	};
}

Mat4& Mat4::operator*=(const Mat4& other)
{
	//	一行目
	//mat[0][0] *= mat[0][0] * other.mat[0][0] + mat[0][1] * other.mat[1][0] +
	//	mat[0][2] * other.mat[2][0] + mat[0][3] * other.mat[3][0];

	//mat[0][1] *= mat[0][0] * other.mat[0][1] + mat[0][1] * other.mat[1][1] +
	//	mat[0][2] * other.mat[2][1] + mat[0][3] * other.mat[3][1];

	//mat[0][2] *= mat[0][0] * other.mat[0][2] + mat[0][1] * other.mat[1][2] +
	//	mat[0][2] * other.mat[2][2] + mat[0][3] * other.mat[3][2];

	//mat[0][3] *= mat[0][0] * other.mat[0][3] + mat[0][1] * other.mat[1][3] +
	//	mat[0][2] * other.mat[2][3] + mat[0][3] * other.mat[3][3];

	//// 二行目
	//mat[1][0] *= mat[1][0] * other.mat[0][0] + mat[1][1] * other.mat[1][0] +
	//	mat[1][2] * other.mat[2][0] + mat[1][3] * other.mat[3][0];

	//mat[1][1] *= mat[1][0] * other.mat[0][1] + mat[1][1] * other.mat[1][1] +
	//	mat[1][2] * other.mat[2][1] + mat[1][3] * other.mat[3][1];

	//mat[1][2] * mat[1][0] * other.mat[0][2] + mat[1][1] * other.mat[1][2] +
	//	mat[1][2] * other.mat[2][2] + mat[1][3] * other.mat[3][2];

	//mat[1][3] *= mat[1][0] * other.mat[0][3] + mat[1][1] * other.mat[1][3] +
	//	mat[1][2] * other.mat[2][3] + mat[1][3] * other.mat[3][3];

	//// 三行目
	//mat[2][0] *= mat[2][0] * other.mat[0][0] + mat[2][1] * other.mat[1][0] +
	//	mat[2][2] * other.mat[2][0] + mat[2][3] * other.mat[3][0];

	//mat[2][1] *= mat[2][0] * other.mat[0][1] + mat[2][1] * other.mat[1][1] +
	//	mat[2][2] * other.mat[2][1] + mat[2][3] * other.mat[3][1];

	//mat[2][2] *= mat[2][0] * other.mat[0][2] + mat[2][1] * other.mat[1][2] +
	//	mat[2][2] * other.mat[2][2] + mat[2][3] * other.mat[3][2];

	//mat[2][3] *= mat[2][0] * other.mat[0][3] + mat[2][1] * other.mat[1][3] +
	//	mat[2][2] * other.mat[2][3] + mat[2][3] * other.mat[3][3];

	//// 四行目
	//mat[3][0] *= mat[3][0] * other.mat[0][0] + mat[3][1] * other.mat[1][0] +
	//	mat[3][2] * other.mat[2][0] + mat[3][3] * other.mat[3][0];

	//mat[3][1] *= mat[3][0] * other.mat[0][1] + mat[3][1] * other.mat[1][1] +
	//	mat[3][2] * other.mat[2][1] + mat[3][3] * other.mat[3][1];

	//mat[3][2] *= mat[3][0] * other.mat[0][2] + mat[3][1] * other.mat[1][2] +
	//	mat[3][2] * other.mat[2][2] + mat[3][3] * other.mat[3][2];

	//mat[3][3] *= mat[3][0] * other.mat[0][3] + mat[3][1] * other.mat[1][3] +
	//	mat[3][2] * other.mat[2][3] + mat[3][3] * other.mat[3][3];

	return *this;
};
