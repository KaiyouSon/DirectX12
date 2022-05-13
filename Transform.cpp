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
	matWorld = XMMatrixIdentity();

	// �X�P�[�����O
	XMMATRIX matScale;	// �X�P�[�����O�s��
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matWorld *= matScale;	// ���[���h�ϊ��s��ɃX�P�[�����O�𔽉f

	// ��]
	XMMATRIX matRot; // ��]�s��
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationX(Radian(rot.x));
	matRot *= XMMatrixRotationY(Radian(rot.y));
	matRot *= XMMatrixRotationZ(Radian(rot.z));
	matWorld *= matRot;

	// ���s�ړ�
	XMMATRIX matTrans;	// ���s�ړ�
	matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);	// ���s�ړ�
	matWorld *= matTrans;	// ���[���h�s��ɕ��s�ړ��𔽉f
}