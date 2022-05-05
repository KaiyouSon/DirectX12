#include "Transform.h"

Transform::Transform()
{

}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
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
	matRot *= XMMatrixRotationX(rot.x);
	matRot *= XMMatrixRotationY(rot.y);
	matRot *= XMMatrixRotationZ(rot.z);
	matWorld *= matRot;

	// ���s�ړ�
	XMMATRIX matTrans;	// ���s�ړ�
	matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);	// ���s�ړ�
	matWorld *= matTrans;	// ���[���h�s��ɕ��s�ړ��𔽉f
}