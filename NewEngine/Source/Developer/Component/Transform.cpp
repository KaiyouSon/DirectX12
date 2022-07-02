#include "NewEngine/Header/Developer/Component/Transform.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
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
	matScale = MathUtil::ConvertScalingMat(scale);		 // �X�P�[�����O
	matRot = Mat4::Identity();
	matRot *= MathUtil::ConvertRotationZAxisMat(rot.z); // z����]
	matRot *= MathUtil::ConvertRotationXAxisMat(rot.x); // x����]
	matRot *= MathUtil::ConvertRotationYAxisMat(rot.y); // y����]
	matTrans = MathUtil::ConvertTranslationMat(pos);	 // ���s�ړ�

	matWorld = Mat4::Identity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;	// ���[���h�s��ɕ��s�ړ��𔽉f
}