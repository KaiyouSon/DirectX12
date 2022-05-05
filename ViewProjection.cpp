#include "ViewProjection.h"
#include "NewEngineWindow.h"

extern NewEngineWindow* newEngineWin;

void ViewProjection::Initialize()
{
	// �r���[�ϊ��s��
	XMFLOAT3 eye(0, 0, -100);	// ���_���W
	XMFLOAT3 target(0, 0, 0);	// �����_���W
	XMFLOAT3 up(0, 1, 0);		// ������x�N�g��
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// �������e�s��̌v�Z
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),	// �㉺��p45�x
		(float)newEngineWin->GetWinWidth() / newEngineWin->GetWinHeight(), // �A�X�y�N�g��(��ʉ���/��ʏc��)
		0.1f, 1000.0f	// ��[�@���[
	);
}