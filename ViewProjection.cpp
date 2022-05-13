#include "ViewProjection.h"
#include "NewEngineWindow.h"
#include "Util.h"

extern NewEngineWindow* newEngineWin;

ViewProjection::ViewProjection() : eye(0, 0, -10), target(0, 0, 0), up(0, 1, 0)
{
	Initialize();
}

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// ���s���e�s��̌v�Z
	matProjection2D = XMMatrixOrthographicOffCenterLH(
		0, WIN_WIDTH,
		WIN_HEIGHT, 0,
		0, 1);

	// �������e�s��̌v�Z
	matProjection3D = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),	// �㉺��p45�x
		(float)WIN_WIDTH / WIN_HEIGHT, // �A�X�y�N�g��(��ʉ���/��ʏc��)
		0.1f, 1000.0f);	// ��[�@���[
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