#include "Header/Transform.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
{
}

Transform::Transform(Vec3 pos, Vec3 scale, Vec3 rot) :
	pos(pos), scale(scale), rot(rot)
{
}

void Transform::Update()
{
	// �X�P�[�����O
	matScale = Mat4::Scale(scale);
	matWorld *= matScale;

	// ��]
	matRot *= Mat4::RotateZ(rot.z);
	matRot *= Mat4::RotateX(rot.x);
	matRot *= Mat4::RotateY(rot.y);
	matWorld *= matRot;

	// ���s�ړ�
	matTrans = Mat4::Translate(pos);
	matWorld *= matTrans;	// ���[���h�s��ɕ��s�ړ��𔽉f
}