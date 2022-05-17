#pragma once
#include "Vec3.h"

class Mat4
{
public:
	float mat[4][4];

	Mat4();
	Mat4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);

	static Mat4 Zero();	// 単位行列を返す関数
	static Mat4 Identity();	// 単位行列を返す関数

	static Mat4 Scale(Vec3 scale);		// スケーリング行列を返す関数
	static Mat4 RotateX(float angle);	// 回転行列ｘ軸を返す関数
	static Mat4 RotateY(float angle);	// 回転行列ｙ軸を返す関数
	static Mat4 RotateZ(float angle);	// 回転行列ｚ軸を返す関数
	static Mat4 Translate(Vec3 pos);	// 平行移動を返す関数

	static Mat4 ViewConversion(const Vec3& pos, const Vec3& target, const Vec3& up);
	static Mat4 PerspectiveConversion(float fovAngle, float aspect, float nearZ, float farZ);

	// 単項演算子オーバーロード
	Mat4 operator*(const Mat4& other) const;

	// 代入演算子オーバーロード
	Mat4& operator*=(const Mat4& other);
};