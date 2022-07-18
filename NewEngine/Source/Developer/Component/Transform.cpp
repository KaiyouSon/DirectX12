#include "NewEngine/Header/Developer/Component/Transform.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0),
	worldMat(Mat4::Identity()), scaleMat(Mat4::Identity()),
	rotMat(Mat4::Identity()), transMat(Mat4::Identity()),
	billboardMat(Mat4::Identity()), isBillBoard(false), billBoardType(0)
{
	componentName = "Transform";
}

Transform::Transform(Vec3 pos, Vec3 scale, Vec3 rot) :
	pos(pos), scale(scale), rot(rot)
{
	componentName = "Transform";
}

void Transform::Update()
{
	scaleMat = MathUtil::ConvertScalingMat(scale);		 // ƒXƒP[ƒŠƒ“ƒO
	rotMat = Mat4::Identity();
	rotMat *= MathUtil::ConvertRotationZAxisMat(rot.z); // zŽ²‰ñ“]
	rotMat *= MathUtil::ConvertRotationXAxisMat(rot.x); // xŽ²‰ñ“]
	rotMat *= MathUtil::ConvertRotationYAxisMat(rot.y); // yŽ²‰ñ“]
	transMat = MathUtil::ConvertTranslationMat(pos);	 // •½sˆÚ“®

	if (isBillBoard == false)	billboardMat = Mat4::Identity();
	else
	{
		if (billBoardType == XAXIS_BILLBOARD)
		{
			billboardMat = Mat4::Inverse(view->matView);
			billboardMat.mat[0][0] = 1;
			billboardMat.mat[0][1] = 0;
			billboardMat.mat[0][2] = 0;
			billboardMat.mat[0][3] = 0;

			billboardMat.mat[3][0] = 0;
			billboardMat.mat[3][1] = 0;
			billboardMat.mat[3][2] = 0;
			billboardMat.mat[3][3] = 1;
		}
		if (billBoardType == YAXIS_BILLBOARD)
		{
			billboardMat = Mat4::Inverse(view->matView);

			billboardMat.mat[1][0] = 0;
			billboardMat.mat[1][1] = 1;
			billboardMat.mat[1][2] = 0;
			billboardMat.mat[1][3] = 0;

			billboardMat.mat[3][0] = 0;
			billboardMat.mat[3][1] = 0;
			billboardMat.mat[3][2] = 0;
			billboardMat.mat[3][3] = 1;
		}
		if (billBoardType == ZAXIS_BILLBOARD)
		{
			billboardMat = Mat4::Inverse(view->matView);

			billboardMat.mat[2][0] = 0;
			billboardMat.mat[2][1] = 0;
			billboardMat.mat[2][2] = 1;
			billboardMat.mat[2][3] = 0;

			billboardMat.mat[3][0] = 0;
			billboardMat.mat[3][1] = 0;
			billboardMat.mat[3][2] = 0;
			billboardMat.mat[3][3] = 1;
		}
		if (billBoardType > 2) billBoardType = 0;
	}

	worldMat = Mat4::Identity();
	worldMat *= scaleMat;
	worldMat *= rotMat;
	worldMat *= billboardMat;
	worldMat *= transMat;
}

void Transform::SetisBillBoard(bool isBillBoard)
{
	this->isBillBoard = isBillBoard;
}
void Transform::SetBillBoardType(int billBoardType)
{
	this->billBoardType = billBoardType;
}

bool Transform::GetisBillBoard()
{
	return isBillBoard;
}
int Transform::GetBillBoardType()
{
	return billBoardType;
}
