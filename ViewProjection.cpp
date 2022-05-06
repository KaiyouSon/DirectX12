#include "ViewProjection.h"
#include "NewEngineWindow.h"

extern NewEngineWindow* newEngineWin;

ViewProjection::ViewProjection() : eye(0, 0, -10), target(0, 0, 0), up(0, 1, 0)
{
	Initialize();
}

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// �������e�s��̌v�Z
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),	// �㉺��p45�x
		(float)newEngineWin->GetWinWidth() / newEngineWin->GetWinHeight(), // �A�X�y�N�g��(��ʉ���/��ʏc��)
		0.1f, 1000.0f	// ��[�@���[
	);
}

void ViewProjection::SetEye(const XMFLOAT3& eye)
{
	this->eye = eye;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void ViewProjection::SetTarget(const XMFLOAT3& target)
{
	this->target = target;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void ViewProjection::SetUp(const XMFLOAT3& up)
{
	this->up = up;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}