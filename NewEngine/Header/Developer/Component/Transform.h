#pragma once
#include "NewEngine/Header/Developer/Component/IComponent.h"
#include "NewEngine/Header/Developer/Math/MathUtil.h"

constexpr int XAXIS_BILLBOARD = 0;
constexpr int YAXIS_BILLBOARD = 1;
constexpr int ZAXIS_BILLBOARD = 2;

class Transform : public IComponent
{
public:
	Vec3 pos;	// ���W
	Vec3 scale;	// �X�P�[��
	Vec3 rot;	// ��]

	// ���[���h�ϊ��s��
	Mat4 worldMat;
private:
	Mat4 scaleMat;	// �X�P�[���s��
	Mat4 rotMat;	// ��]�s��
	Mat4 transMat;	// ���s�ړ��s��
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

