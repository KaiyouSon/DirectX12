#pragma once
#include <math.h>
#include "NewEngine/Header/Developer/Math/Vec2.h"
#include "NewEngine/Header/Developer/Math/Vec3.h"
#include "NewEngine/Header/Developer/Math/Vec4.h"
#include "NewEngine/Header/Developer/Math/Mat4.h"
#include "NewEngine/Header/Developer/Math/Quaternion.h"

class MathUtil
{
public:
	static const float PI;

	// 絶対値を返す関数
	static float Absolut(float num);

	// 弧度法から度数法に変換する関数
	static float Angle(float radian);
	static Vec2 Angle(Vec2 radian);
	static Vec3 Angle(Vec3 radian);
	// 度数法から弧度法に変換する関数
	static float Radian(float angle);
	static Vec2 Radian(Vec2 angle);
	static Vec3 Radian(Vec3 angle);

	Vec2 ConvertVec3ToVec2(Vec3 vec);	// 3次元ベクトルを2次元ベクトルに変換
	Vec3 ConvertVec2ToVec3(Vec2 vec);	// 2次元ベクトルを3次元ベクトルに変換

	static Mat4 ConvertQuaternionToRotationMat(Quaternion q);	// クォータニオンを回転行列に変える

	static Mat4 ConvertScalingMat(Vec3 scale);		// スケーリング行列を返す関数
	static Mat4 ConvertRotationXAxisMat(float angle);	// 回転行列ｘ軸を返す関数
	static Mat4 ConvertRotationYAxisMat(float angle);	// 回転行列ｙ軸を返す関数
	static Mat4 ConvertRotationZAxisMat(float angle);	// 回転行列ｚ軸を返す関数
	static Mat4 ConvertTranslationMat(const Vec3& pos);	// 平行移動を返す関数

	static Mat4 ConvertViewProjectionMat(const Vec3& pos, const Vec3& target, const Vec3& up);			// ビュー変換
	static Mat4 ConvertPerspectiveProjectionMat(float fovAngle, float aspect, float nearZ, float farZ);	// 透視射影変換
	static Mat4 ConvertOrthoGrphicProjectionMat(int WIN_WIDTH, int WIN_HEIGHT);							// 平行射影変換
};