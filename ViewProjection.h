#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class ViewProjection
{
private:
	XMFLOAT3 eye;	// ���_���W
	XMFLOAT3 target;	// �����_���W
	XMFLOAT3 up;		// ������x�N�g��

public:
	// �r���[�ϊ��s��
	XMMATRIX matView;

	// �������e�s��̌v�Z
	XMMATRIX matProjection;

public:
	ViewProjection();
	void Initialize();

	void SetEye(const XMFLOAT3& eye);
	void SetTarget(const XMFLOAT3& target);
	void SetUp(const XMFLOAT3& up);
};