#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"

constexpr int XAXIS_BILLBOARD = 0;
constexpr int YAXIS_BILLBOARD = 1;
constexpr int ZAXIS_BILLBOARD = 2;

class Transform : public IComponent
{
public:
	Vec3 pos;	// 座標
	Vec3 scale;	// スケール
	Vec3 rot;	// 回転

	// ワールド変換行列
	Mat4 worldMat;
private:
	Mat4 scaleMat;	// スケール行列
	Mat4 rotMat;	// 回転行列
	Mat4 transMat;	// 平行移動行列
	Mat4 billboardMat;

	bool isBillBoard;
	int billBoardType;
public:
	Transform();
	Transform(Vec3 pos, Vec3 scale, Vec3 rot);
	void Update();

	void SetisBillBoard(bool isBillBoard);
	void SetBillBoardType(int billBoardType);

	bool GetisBillBoard();
	int GetBillBoardType();


};

