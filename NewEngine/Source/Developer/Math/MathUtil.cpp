#include "NewEngine/Header/Developer/Math/MathUtil.h"

const float MathUtil::PI = 3.141592f;

float MathUtil::Angle(float radian)
{
	return radian * 360 / (2 * PI);
}
Vec2 MathUtil::Angle(Vec2 radian)
{
	return { Angle(radian.x),Angle(radian.y) };
}
Vec3 MathUtil::Angle(Vec3 radian)
{
	return { Angle(radian.x),Angle(radian.y),Angle(radian.z) };
}

float MathUtil::Radian(float angle)
{
	return angle * (2 * PI) / 360;
}
Vec2 MathUtil::Radian(Vec2 angle)
{
	return { Radian(angle.x),Radian(angle.y) };
}
Vec3 MathUtil::Radian(Vec3 angle)
{
	return { Radian(angle.x),Radian(angle.y),Radian(angle.z) };
}

Vec2 MathUtil::ConvertVec3ToVec2(Vec3 vec)
{
	return { vec.x,vec.y };
}
Vec3 MathUtil::ConvertVec2ToVec3(Vec2 vec)
{
	return { vec.x,vec.y,0 };
}

float MathUtil::Absolut(float num)
{
	if (num > 0)		return num;
	else if (num < 0)	return num * -1;
	else				return 0;
}

Mat4 MathUtil::ConvertScalingMat(Vec3 scale)
{
	return
	{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1
	};
}
Mat4 MathUtil::ConvertRotationXAxisMat(float angle)
{
	return
	{
		1,0,0,0,
		0, cosf(MathUtil::Radian(angle)),sinf(MathUtil::Radian(angle)),0,
		0,-sinf(MathUtil::Radian(angle)),cosf(MathUtil::Radian(angle)),0,
		0,0,0,1
	};
}
Mat4 MathUtil::ConvertRotationYAxisMat(float angle)
{
	return
	{
		cosf(MathUtil::Radian(angle)),0,-sinf(MathUtil::Radian(angle)),0,
		0,1,0,0,
		sinf(MathUtil::Radian(angle)),0, cosf(MathUtil::Radian(angle)),0,
		0,0,0,1
	};
}
Mat4 MathUtil::ConvertRotationZAxisMat(float angle)
{
	return
	{
		 cosf(MathUtil::Radian(angle)),sinf(MathUtil::Radian(angle)),0,0,
		-sinf(MathUtil::Radian(angle)),cosf(MathUtil::Radian(angle)),0,0,
		0,0,1,0,
		0,0,0,1
	};
}
Mat4 MathUtil::ConvertTranslationMat(const Vec3& pos)
{
	return
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		pos.x,pos.y,pos.z,1
	};
}
Mat4 MathUtil::ConvertQuaternionToRotationMat(Quaternion q)
{
	Mat4 rotationMat = Mat4::Identity();
	rotationMat.mat[0][0] = 1 - (2 * (q.y * q.y)) - (2 * (q.z * q.z));
	rotationMat.mat[0][1] = (2 * q.x * q.y) + (2 * q.w * q.z);
	rotationMat.mat[0][2] = (2 * q.x * q.z) - (2 * q.w * q.y);
	rotationMat.mat[0][3] = 0;

	rotationMat.mat[1][0] = (2 * q.x * q.y) - (2 * q.w * q.z);
	rotationMat.mat[1][1] = 1 - (2 * (q.x * q.x)) - (2 * (q.z * q.z));
	rotationMat.mat[1][2] = (2 * q.y * q.z) + (2 * q.w * q.x);
	rotationMat.mat[1][3] = 0;

	rotationMat.mat[2][0] = (2 * q.x * q.z) + (2 * q.w * q.y);
	rotationMat.mat[2][1] = (2 * q.y * q.z) - (2 * q.w * q.x);
	rotationMat.mat[2][2] = 1 - (2 * (q.x * q.x)) - (2 * (q.y * q.y));
	rotationMat.mat[2][3] = 0;

	rotationMat.mat[3][0] = 0;
	rotationMat.mat[3][1] = 0;
	rotationMat.mat[3][2] = 0;
	rotationMat.mat[3][3] = 1;

	return rotationMat;
}

Mat4 MathUtil::ConvertViewProjectionMat(const Vec3& pos, const Vec3& target, const Vec3& up)
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
Mat4 MathUtil::ConvertPerspectiveProjectionMat(float fovAngle, float aspect, float nearZ, float farZ)
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
Mat4 MathUtil::ConvertOrthoGrphicProjectionMat(int WIN_WIDTH, int WIN_HEIGHT)
{
	return
	{
		2 / (float)WIN_WIDTH,0,0,0,
		0,-2 / (float)WIN_HEIGHT,0,0,
		0,0,1,0,
		-1,1,0,1
	};
}