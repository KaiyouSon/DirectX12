#include "ViewProjection.h"
#include "NewEngineWindow.h"

extern NewEngineWindow* newEngineWin;

void ViewProjection::Initialize()
{
	// ビュー変換行列
	XMFLOAT3 eye(0, 0, -100);	// 視点座標
	XMFLOAT3 target(0, 0, 0);	// 注視点座標
	XMFLOAT3 up(0, 1, 0);		// 上方向ベクトル
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

	// 透視投影行列の計算
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45),	// 上下画角45度
		(float)newEngineWin->GetWinWidth() / newEngineWin->GetWinHeight(), // アスペクト比(画面横幅/画面縦幅)
		0.1f, 1000.0f	// 先端　奥端
	);
}