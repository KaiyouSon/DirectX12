#include "Transform.h"

Transform::Transform()
{

}

Transform::Transform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 rot)
{
}

void Transform::Update()
{
	//// �P�ʍs�����
	//constMapTransform->mat = XMMatrixIdentity();

	//constMapTransform->mat.r[0].m128_f32[0] = 2.0f / newEngineWin->GetWinWidth();
	//constMapTransform->mat.r[1].m128_f32[1] = -2.0f / newEngineWin->GetWinHeight();

	//constMapTransform->mat.r[3].m128_f32[0] = -1.0f;
	//constMapTransform->mat.r[3].m128_f32[1] = 1.0f;

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