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
	// ビュー変換行列
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// 並行投影行列の計算
	matProjection2D = XMMatrixOrthographicOffCenterLH(
		0, WIN_WIDTH,
		WIN_HEIGHT, 0,
		0, 1);

	// 透視投影行列の計算
	matProjection3D = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),	// 上下画角45度
		(float)WIN_WIDTH / WIN_HEIGHT, // アスペクト比(画面横幅/画面縦幅)
		0.1f, 1000.0f);	// 先端　奥端
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