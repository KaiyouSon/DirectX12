#include "Transform.h"
#include "MathUtil.h"

Transform::Transform() :
	pos(0, 0, 0), scale(1, 1, 1), rot(0, 0, 0)
{
}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot) :
	pos(pos), scale(scale), rot(rot)
{
}

void Transform::Update()
{
	// ���[���h�ϊ��s��
	//matWorld = XMMatrixIdentity();
	matWorld = Mat4::Identity();

	// �X�P�[�����O
	//XMMATRIX matScale;	// �X�P�[�����O�s��
	//matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	//matWorld *= matScale;	// ���[���h�ϊ��s��ɃX�P�[�����O�𔽉f
	Mat4 matScale = Mat4::Scale(Vec3(scale.x, scale.y, scale.z));
	matWorld *= matScale;

	// ��]
	//XMMATRIX matRot; // ��]�s��
	//matRot = XMMatrixIdentity();
	//matRot *= XMMatrixRotationX(Radian(rot.x));
	//matRot *= XMMatrixRotationY(Radian(rot.y));
	//matRot *= XMMatrixRotationZ(Radian(rot.z));

	Mat4 matRot = Mat4::Identity();
	matRot *= Mat4::RotateZ(rot.z);
	matRot *= Mat4::RotateX(rot.x);
	matRot *= Mat4::RotateY(rot.y);
	matWorld *= matRot;

	// ���s�ړ�
	//XMMATRIX matTrans;	// ���s�ړ�
	//matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);	// ���s�ړ�

	Mat4 matTrans = Mat4::Identity();
	matTrans = Mat4::Translate(Vec3(pos.x, pos.y, pos.z));
	matWorld *= matTrans;	// ���[���h�s��ɕ��s�ړ��𔽉f
}